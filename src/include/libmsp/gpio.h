#ifndef LIBMSP_GPIO_H
#define LIBMSP_GPIO_H

#ifdef __MSP430FR5969__
#define msp_gpio_unlock() PM5CTL0 &= ~LOCKLPM5
#else // !__MSP430RF5969__
#define msp_gpio_unlock()
#endif // !__MSP430RF5969__

#endif // LIBMSP_GPIO_H
