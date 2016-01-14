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


/**
 * Two alternative workarounds for the crashes due to voltage ramp on startup
 * 		  The problem these work around is crashes that occur at arbitrary times
 *         after startup. The crash is either a wild jump or an oscillator
 *         fault.
 *
 *         At first glance crashes are somewhat consistent and seem
 *         correlated to peripheral activity. For example, not doing anything
 *         with the UART might seem to get rid of the crash, or, even
 *         stranger, re-arranging C-code, like removing code that's in an
 *         if-branch that is never taken, or replacing a function call with an
 *         inline invocation, all appear to consistently influence whether a
 *         crash happens or not.
 *
 *         However, the underlying issue is traced to some kind of
 *         non-fail-stop failure during startup that corrupts subsequent
 *         execution. Furthermore, the problem has to do with the Power
 *         Management Module -- it either generates false events (like
 *         overvoltage), or does not generate correct events in time. In
 *         particular, there are multiple errata about it, including a false
 *         overvoltage even if voltage ramps up too quickly.
 *
 *         NOTE: Unfortunately, these workarounds do not get rid of the same kind
 *               of crash that happens with debugger attached (either CCSv6 or
 *               mspdebug).
 */
#define CONFIG_STARTUP_VOLTAGE_WORKAROUND_DISABLE_PMM
// #define CONFIG_STARTUP_VOLTAGE_WORKAROUND_DELAY

#else // __MSP430*__
#error Device not supported by libmsp/clock.c
#endif // __MSP430*__

#endif // LIBMSP_CLOCK_CONFIG_H
