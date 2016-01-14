#ifndef LIBMSP_CLOCK_CONFIG_H
#define LIBMSP_CLOCK_CONFIG_H

#if defined(__MSP430F5340__)

// These are fixed constants properties of MCU and/or board
#define CONFIG_REFO_FREQ 32768ull

#define CONFIG_XT1_FREQ 32768ull
#define CONFIG_XT1_CAP 12 // pF

// TODO: This one is the odd ball: it depends on the board, not only on device
#define CONFIG_XT2_FREQ 12000000ull
// #define CONFIG_XT2_FREQ 25000000

// #define CONFIG_DCO_REF_SOURCE_REFO
// #define CONFIG_DCO_REF_CLOCK_DIV 1

//#define CONFIG_DCO_REF_SOURCE_XT1
//#define CONFIG_DCO_REF_CLOCK_DIV 1

#define CONFIG_DCO_REF_SOURCE_XT2
#define CONFIG_DCO_REF_CLOCK_DIV 4

#define CONFIG_CLOCK_SOURCE_DCO
// #define CONFIG_CLOCK_SOURCE_XT2

// #define CONFIG_DCOCLKDIV_FREQ 24576000ull
#define CONFIG_DCOCLKDIV_FREQ 24000000ull
// #define CONFIG_DCOCLKDIV_FREQ 21921792ull
// #define CONFIG_DCOCLKDIV_FREQ 16384000ull
// #define CONFIG_DCOCLKDIV_FREQ 12288000ull
// #define CONFIG_DCOCLKDIV_FREQ 8192000ull

#define CONFIG_CLK_DIV_MCLK         1
#define CONFIG_CLK_DIV_SMCLK        1
#define CONFIG_CLK_DIV_ACLK         1

#else // __MSP430*__
#error Device not supported by libmsp/clock.c
#endif // __MSP430*__

#endif // LIBMSP_CLOCK_CONFIG_H
