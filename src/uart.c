#include <msp430.h>

#include <stdint.h>
#include <stdbool.h>

#include "periph.h"
#include <libmspbuiltins/builtins.h>
#include "uart.h"

static uint8_t *tx_data;
static unsigned tx_len;
static volatile bool tx_finished;

void msp_uart_open()
{
    UART_SET_SEL(LIBMSP_UART_PIN_TX_PORT, BIT(LIBMSP_UART_PIN_TX_PIN));

    UART(LIBMSP_UART_IDX, CTL1) |= UCSWRST; // put state machine in reset
    UART(LIBMSP_UART_IDX, CTL1) |= CONCAT(UCSSEL__, LIBMSP_UART_CLOCK);

    UART_SET_BR(LIBMSP_UART_IDX, LIBMSP_UART_BAUDRATE_BR);
    UART_MCTL(LIBMSP_UART_IDX) = UCBRF_0 | UART_BRS(LIBMSP_UART_BAUDRATE_BRS);

    UART(LIBMSP_UART_IDX, CTL1) &= ~UCSWRST; // turn on
}

void msp_uart_close()
{
    UART(LIBMSP_UART_IDX, CTL1) |= UCSWRST;
}

void msp_uart_send_sync(uint8_t *payload, unsigned len)
{
    if (len == 0)
        return;

    // Setup pointers for the ISR
    tx_data = payload;
    tx_len = len;
    tx_finished = false;
    UART(LIBMSP_UART_IDX, IE) |= UCTXIE;

// On the CC430 family, the ISR does not fire as a result of enabling IE
// (despite IFG being on). We need to write a byte to clear the IFG, and await
// the interrupt. Also, the TXIFG behavior is different, see ISR.
#ifdef __CC430__
    --tx_len;
    UART(LIBMSP_UART_IDX, TXBUF) = *tx_data++; // first byte, clears IFG
#endif

    // Sleep, while ISR TXes the remaining bytes
    //
    // We have to disable TX int from ISR, otherwise, will enter infinite ISR loop.
    __disable_interrupt(); // classic lock-check-(sleep+unlock)-lock pattern
    while (!tx_finished) {
        __bis_SR_register(LPM0_bits + GIE); // will wakeup after ISR TXes last byte
        __disable_interrupt();
    }
    __enable_interrupt();

    // TXCPTIFG (and TXIFG) both happen before the byte is
    // transfered... so have to busywait
    while (UART(LIBMSP_UART_IDX, STATW) & UCBUSY);
}

__attribute__ ((interrupt(UART_VECTOR(LIBMSP_UART_IDX))))
void UART_ISR(LIBMSP_UART_IDX) (void)
{
    switch(__even_in_range(UART(LIBMSP_UART_IDX, IV), 0x08)) {
        case UART_INTFLAG(TXIFG):

// On CC430, the TXIFG fires when tx has finished, whereas
// on MSP430FR, TXIFG fires when is ready to accept the next byte, which
// happens before the last has finished transmitting byte. Hence, the
// logic in the ISR is different.
#ifdef __CC430__
            if (tx_len--) {
                UART(LIBMSPUARTLINK_UART_IDX, TXBUF) = *tx_data++;
            } else { // last byte got done
                tx_finished = true;
                __bic_SR_register_on_exit(LPM4_bits); // wakeup
            }
#else // !__CC430__
            UART(LIBMSP_UART_IDX, TXBUF) = *tx_data++;
            if (--tx_len == 0) {
                UART(LIBMSP_UART_IDX, IE) &= ~UCTXIE;
                UART(LIBMSP_UART_IDX, IFG) &= ~UCTXCPTIFG;
                UART(LIBMSP_UART_IDX, IE) |= UCTXCPTIE;
            }
#endif // !__CC430__
            break;
        case UART_INTFLAG(RXIFG):
            break;
        case UART_INTFLAG(TXCPTIFG):
            tx_finished = true;
            __bic_SR_register_on_exit(LPM4_bits); // wakeup
            break;
        default:
            break;
    }
}
