#include <msp430.h>

#include "periph.h"

#include "sleep.h"

#define TIMER_NAME_INNER_INNER(type, id) type ## id
#define TIMER_NAME_INNER(type, id) TIMER_NAME_INNER_INNER(type, id)
#define SLEEP_TIMER TIMER_NAME_INNER(LIBMSP_SLEEP_TIMER_TYPE, LIBMSP_SLEEP_TIMER_IDX)

void msp_sleep(unsigned cycles)
{
    TIMER(SLEEP_TIMER, CTL) |= TIMER_CLK_SOURCE_BITS(LIBMSP_SLEEP_TIMER_TYPE, LIBMSP_SLEEP_TIMER_CLK) |
                               TIMER_CLR(LIBMSP_SLEEP_TIMER_TYPE);
    TIMER_CC(SLEEP_TIMER, LIBMSP_SLEEP_TIMER_CC, CCR) = cycles;
    TIMER_CC(SLEEP_TIMER, LIBMSP_SLEEP_TIMER_CC, CCTL) &= ~CCIFG;
    TIMER_CC(SLEEP_TIMER, LIBMSP_SLEEP_TIMER_CC, CCTL) |= CCIE;

    // The int disable/enable implement the classic check-and-sleep pattern
    __disable_interrupt();
    TIMER(SLEEP_TIMER, CTL) |= MC_1; // start timer

    while (TIMER_CC(SLEEP_TIMER, LIBMSP_SLEEP_TIMER_CC, CCTL) & CCIE) { // might not be our ISR
        __bis_SR_register(LPM4_bits + GIE); // enable interrupt and go to sleep
        __disable_interrupt();
    }
    __enable_interrupt();
}

// We declare the ISR in the library, which disallows sequential multiplexing of this timer.
// Note: there's no concurrent multiplexing of the timer (at least not in this
// simple design), so the ISR can be hidden in the library.
__attribute__ ((interrupt(TIMER_VECTOR(LIBMSP_SLEEP_TIMER_TYPE, LIBMSP_SLEEP_TIMER_IDX, LIBMSP_SLEEP_TIMER_CC))))
void  TIMER_ISR(LIBMSP_SLEEP_TIMER_TYPE, LIBMSP_SLEEP_TIMER_IDX, LIBMSP_SLEEP_TIMER_CC) (void)
{
    TIMER(SLEEP_TIMER, CTL) &= ~MC_1; // stop timer
    TIMER_CC(SLEEP_TIMER, LIBMSP_SLEEP_TIMER_CC, CCTL) &= ~CCIE; // used as flag that ISR ran
    // CCIFG automatically reset

    // We were sleeping waiting for interrupt, so exit sleep
    __bic_SR_register_on_exit(LPM4_bits);
}
