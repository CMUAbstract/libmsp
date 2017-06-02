#include <msp430.h>

#include <stdint.h>
#include "periph.h"

#include "uart.h"

static uint8_t *tx_data;
static unsigned tx_len;

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
    tx_len = len - 1;
    UART(LIBMSP_UART_IDX, IE) |= UCTXIE;
    UART(LIBMSP_UART_IDX, TXBUF) = *tx_data++; // first byte, clears IFG

    // Sleep, while ISR TXes the remaining bytes
    //
    // We have to disable TX int from ISR, otherwise, will enter infinite ISR loop.
    // So, we might as well use it as the sleep flag.
    __disable_interrupt(); // classic lock-check-(sleep+unlock)-lock pattern
    while (UART(LIBMSP_UART_IDX, IE) & UCTXIE) {
        __bis_SR_register(LPM0_bits + GIE); // will wakeup after ISR TXes last byte
        __disable_interrupt();
    }
    __enable_interrupt();
}

__attribute__ ((interrupt(UART_VECTOR(LIBMSP_UART_IDX))))
void UART_ISR(LIBMSP_UART_IDX) (void)
{
    switch(__even_in_range(UART(LIBMSP_UART_IDX, IV), 0x08)) {
        case UART_INTFLAG(TXIFG):
            if (tx_len--) {
                UART(LIBMSP_UART_IDX, TXBUF) = *tx_data++;
            } else { // last byte got done
                UART(LIBMSP_UART_IDX, IE) &= ~UCTXIE;
                __bic_SR_register_on_exit(LPM4_bits); // wakeup
            }
            break; // nothing to do, main thread is sleeping, so just wakeup
        case UART_INTFLAG(RXIFG):
            break;
        default:
            break;
    }
}
