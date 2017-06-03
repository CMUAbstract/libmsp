#ifndef LIBMSP_PERIPH_H
#define LIBMSP_PERIPH_H

#include <msp430.h>

#define CONCAT_INNER(a, b) a ## b
#define CONCAT(a, b) CONCAT_INNER(a, b)

#define CONCAT3_INNER(a, b, c) a ## b ## c
#define CONCAT3(a, b, c) CONCAT3_INNER(a, b, c)

#define CONCAT4_INNER(a, b, c, d) a ## b ## c ## d
#define CONCAT4(a, b, c, d) CONCAT4_INNER(a, b, c, d)

#define BIT_INNER(idx) BIT ## idx
#define BIT(idx) BIT_INNER(idx)

#define GPIO_INNER(port, reg) P ## port ## reg
#define GPIO(port, reg) GPIO_INNER(port, reg)

#define INTFLAG_INNER(port, pin) P ## port ## IV_ ## P ## port ## IFG ## pin
#define INTFLAG(port, pin) INTFLAG_INNER(port, pin)

#define INTVEC_INNER(port) P ## port ## IV
#define INTVEC(port) INTVEC_INNER(port)

#define INTVEC_RANGE_INNER(port) P ## port ## IV_P ## port ## IFG7
#define INTVEC_RANGE(port) INTVEC_RANGE_INNER(port)

#define TIMER_INNER(name, reg) T ## name ## reg
#define TIMER(name, reg) TIMER_INNER(name, reg)

#define TIMER_CC_INNER(name, ccridx, reg) T ## name ## reg ## ccridx
#define TIMER_CC(name, ccridx, reg) TIMER_CC_INNER(name, ccridx, reg)

// Legacy
#define TIMERA_INTFLAG_INNER(id, ccridx) T ## id ## IV_ ## TACCR ## ccridx
#define TIMERA_INTFLAG(id, ccridx) TIMERA_INTFLAG_INNER(id, ccridx)

#define TIMER_INTFLAG_INNER(type, idx, ccridx) T ## type ## idx ## IV_ ## T ## type ## CCR ## ccridx
#define TIMER_INTFLAG(type, idx, ccridx) TIMER_INTFLAG_INNER(type, idx, ccridx)

// There is only a IV (flag vector) register for vector 1, not 0 for either timer type
#define TIMER_INTVEC_INNER(type, idx) T ## type ## idx ## IV
#define TIMER_INTVEC(type, idx) TIMER_INTVEC_INNER(type, idx)

#define UART_INNER(idx, reg) UCA ## idx ## reg
#define UART(idx, reg) UART_INNER(idx, reg)

#if defined(__CC430__)

#define UART_MCTL(idx) UART_INNER(idx, MCTL)
#define UART_BRS_INNER(brs) UCBRS_ ## brs
#define UART_BRS(brs) UART_BRS_INNER(brs)
#define UART_INTFLAG(flag) CONCAT(USCI_UC, flag)

#define UART_SET_BR(idx, br) do { \
    UART(idx, BR0) = br & 0xff; \
    UART(idx, BR1) = br >> 8; \
} while (0)


#elif defined(__MSP430FR__)

#define UART_MCTL(idx) UART_INNER(idx, MCTLW)
#define UART_BRS(brs) (brs << 8)
#define UART_INTFLAG(flag) CONCAT(USCI_UART_UC, flag)

#define UART_SET_BR(idx, br) do { \
    UART(idx, BRW) = br; \
} while (0)

#else // FAMILY
#error Unsupported MCU family
#endif // FAMILY

#if defined(__CC430F5137__)

#define UART_SET_SEL(port, pin_bits) do { \
    GPIO(port, SEL) |= (pin_bits); \
} while (0)

#elif defined(__MSP430FR5969__) || defined(__MSP430FR5949__)

#define UART_SET_SEL(port, pin_bits) do { \
    GPIO(port, SEL0) &= ~(pin_bits); \
    GPIO(port, SEL1) |= (pin_bits); \
} while (0)

#elif defined(__MSP430FR6989__)

#define UART_SET_SEL(port, pin_bits) do { \
    GPIO(port, SEL0) |= (pin_bits); \
    GPIO(port, SEL1) &= ~(pin_bits); \
} while (0)

#else // DEVICE
#error MCU not supported
#endif // DEVICE


#define UART_VECTOR_INNER(idx) USCI_A ## idx ## _VECTOR
#define UART_VECTOR(idx) UART_VECTOR_INNER(idx)

#define UART_ISR_INNER(idx) USCI_A ## idx ## _ISR
#define UART_ISR(idx) UART_ISR_INNER(idx)

#define BRS_BITS_INNER(brs) UCBRS_ ## brs
#define BRS_BITS(brs) BRS_BITS_INNER(brs)

#define BRF_BITS_INNER(brf) UCBRF_ ## brf
#define BRF_BITS(brf) BRF_BITS_INNER(brf)

#define DMA_INNER(name, reg) DMA ## name ## reg
#define DMA(name, reg) DMA_INNER(name, reg)

#define DMA_CTL_INNER(chan) DMACTL ## chan
#define DMA_CTL(chan) DMA_CTL_INNER(chan)

#define DMA_TRIG_INNER(chan, trig) DMA ## chan ## TSEL__ ## trig
#define DMA_TRIG(chan, trig) DMA_TRIG_INNER(chan, trig)

#define DMA_TRIG_UART_INNER(idx, dir) USCIA ## idx ## dir
#define DMA_TRIG_UART(idx, dir) DMA_TRIG_UART_INNER(idx, dir)

#define DMA_INTFLAG_INNER(name) DMAIV_DMA ## name ## IFG
#define DMA_INTFLAG(name) DMA_INTFLAG_INNER(name)

#define TIMER_DIV_BITS_INNER(div) ID__ ## div
#define TIMER_DIV_BITS(div) TIMER_DIV_BITS_INNER(div)

#define TIMER_DIVEX_BITS_INNER(type, div) T ## type ## IDEX__ ## div
#define TIMER_DIVEX_BITS(type, div) TIMER_DIVEX_BITS_INNER(type, div)

#define TIMER_CLK_SOURCE_BITS_INNER(mod, src) T ## mod ## SSEL__ ## src
#define TIMER_CLK_SOURCE_BITS(mod, src) TIMER_CLK_SOURCE_BITS_INNER(mod, src)

#define TIMER_CLR_INNER(mod)  T ## mod ## CLR
#define TIMER_CLR(mod) TIMER_CLR_INNER(mod)

#define GPIO_ISR_INNER(port) PORT ## port ## _ISR
#define GPIO_ISR(port) GPIO_ISR_INNER(port)

#define GPIO_VECTOR_INNER(port) PORT ## port ## _VECTOR
#define GPIO_VECTOR(port) GPIO_VECTOR_INNER(port)

// On MSP430, CCR0 gets a dedicated vector, the rest share one vector
#define TIMER_CCR_VECTOR_0 0
#define TIMER_CCR_VECTOR_1 1
#define TIMER_CCR_VECTOR_2 1
#define TIMER_CCR_VECTOR_3 1
#define TIMER_CCR_VECTOR_4 1
#define TIMER_CCR_VECTOR_5 1
#define TIMER_CCR_VECTOR_6 1
#define TIMER_CCR_VECTOR_7 1

#define TIMER_CCR_VECTOR_INNER_INNER(ccr) TIMER_CCR_VECTOR_ ## ccr
#define TIMER_CCR_VECTOR_INNER(ccr) TIMER_CCR_VECTOR_INNER_INNER(ccr)
#define TIMER_CCR_VECTOR(ccr) TIMER_CCR_VECTOR_INNER(ccr)

#define TIMER_VECTOR_INNER_INNER(type, idx, vect) TIMER ## idx ## _ ## type ## vect ## _VECTOR
#define TIMER_VECTOR_INNER(type, idx, vect) TIMER_VECTOR_INNER_INNER(type, idx, vect)
#define TIMER_VECTOR(type, idx, ccr) TIMER_VECTOR_INNER(type, idx, TIMER_CCR_VECTOR(ccr))

#define TIMER_ISR_INNER_INNER(type, idx, vect) TIMER ## idx ## _ ## type ## vect ## _ISR
#define TIMER_ISR_INNER(type, idx, vect) TIMER_ISR_INNER_INNER(type, idx, vect)
#define TIMER_ISR(type, idx, ccr) TIMER_ISR_INNER(type, idx, TIMER_CCR_VECTOR(ccr))

#define DCO_FREQ_RANGE_BITS_INNER(r) DCORSEL_ ## r;
#define DCO_FREQ_RANGE_BITS(r) DCO_FREQ_RANGE_BITS_INNER(r)

#define FLL_D_BITS_INNER(d) FLLD_ ## d
#define FLL_D_BITS(d) FLL_D_BITS_INNER(d)

#define FLL_REF_DIV_BITS_INNER(div) FLLREFDIV__ ## div
#define FLL_REF_DIV_BITS(div) FLL_REF_DIV_BITS_INNER(div)

#define CLK_DIV_BITS_INNER(clk, div) DIV ## clk ## __ ## div
#define CLK_DIV_BITS(clk, div) CLK_DIV_BITS_INNER(clk, div)

#define COMP_INNER(type, arg) C ## type ## arg
#define COMP(type, arg) COMP_INNER(type, arg)

#define COMP2_INNER(type, arg1, arg2) C ## type ## arg1 ## arg2
#define COMP2(type, arg1, arg2) COMP2_INNER(type, arg1, arg2)

#define COMP_VECTOR_INNER(type) COMP_ ## type ## _VECTOR
#define COMP_VECTOR(type) COMP_VECTOR_INNER(type)

#define COMP_INTFLAG_INNER(type, flag) C ## type ## IV_ ## flag
#define COMP_INTFLAG(type, flag) COMP_INTFLAG_INNER(type, flag)

// Compat to handle inconsistency in TI's header
#define CBIV_IFG  CBIV_CBIFG
#define CBIV_IIFG CBIV_CBIIFG

// Legacy. Superceded by COMP() and COMP2().
#define COMP_REF_INNER(level_idx) CEREF0_ ## level_idx
#define COMP_REF(level_idx) COMP_REF_INNER(level_idx)

#define COMP_CHAN_SEL_INNER(idx) CEIPSEL_ ## idx
#define COMP_CHAN_SEL(idx) COMP_CHAN_SEL_INNER(idx)

#define COMP_PIN_INPUT_BUF_DISABLE_INNER(chan_idx) CEPD ## chan_idx
#define COMP_PIN_INPUT_BUF_DISABLE(chan_idx) COMP_PIN_INPUT_BUF_DISABLE_INNER(chan_idx)

#define WATCHDOG_BITS_INNER(clk, interval) (WDTSSEL__ ## clk | WDTIS__ ## interval)
#define WATCHDOG_BITS(clk, interval) WATCHDOG_BITS_INNER(clk, interval)

// Fill-in value-keyd macros that are missing from TI's headers
#define TAIDEX__1 TAIDEX_0
#define TAIDEX__2 TAIDEX_1
#define TAIDEX__3 TAIDEX_2
#define TAIDEX__4 TAIDEX_3
#define TAIDEX__5 TAIDEX_4
#define TAIDEX__6 TAIDEX_5
#define TAIDEX__7 TAIDEX_6
#define TAIDEX__8 TAIDEX_7

#if defined(__MSP430F5340__) || defined(__CC430F5137__) || defined(__MSP430FR6989) || defined(__MSP430FR5949)
// Ugly workaround to make the pretty GPIO macro work for OUT register
// (a control bit for TAxCCTLx uses the name 'OUT'): rename to OUT to TOUT.
enum {
	TOUT = OUT,
};
#undef OUT
#endif

#endif // LIBMSP_PERIPH_H
