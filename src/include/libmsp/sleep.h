#ifndef LIBMSP_SLEEP_H
#define LIBMSP_SLEEP_H

// Go to sleep and set a timer to wake up in (ACLK) cycles
// On MSP430FR5949 the default ACLK is VLOCLK at ~10kHz.
void msp_sleep(unsigned cycles);

#endif // LIBMSP_SLEEP_H
