#include <msp430.h>

void msp_watchdog_disable()
{
     WDTCTL = WDTPW + WDTHOLD;
}
