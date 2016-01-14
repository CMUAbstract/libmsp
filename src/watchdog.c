#include <msp430.h>

#include "watchdog.h"

void msp_watchdog_enable(uint8_t bits)
{
    WDTCTL = WDTPW | WDTCNTCL | bits;
}

void msp_watchdog_disable()
{
     WDTCTL = WDTPW + WDTHOLD;
}
