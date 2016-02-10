#ifndef LIBMSP_PERIPH_H
#define LIBMSP_PERIPH_H

#include <msp430.h>

#define CONCAT_INNER(a, b) a ## b
#define CONCAT(a, b) CONCAT_INNER(a, b)

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

#define TIMERA_INTFLAG_INNER(id, ccridx) T ## id ## IV_ ## TACCR ## ccridx
#define TIMERA_INTFLAG(id, ccridx) TIMERA_INTFLAG_INNER(id, ccridx)

#define UART_INNER(idx, reg) UCA ## idx ## reg
#define UART(idx, reg) UART_INNER(idx, reg)

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

#define TIMER_A_DIV_EX_BITS_INNER(div) TAIDEX_ ## div
#define TIMER_A_DIV_EX_BITS(div) TIMER_A_DIV_EX_BITS_INNER(div - 1)

#define TIMER_CLK_SOURCE_BITS_INNER(mod, src) T ## mod ## SSEL__ ## src
#define TIMER_CLK_SOURCE_BITS(mod, src) TIMER_CLK_SOURCE_BITS_INNER(mod, src)

#define TIMER_CLR_INNER(mod)  T ## mod ## CLR
#define TIMER_CLR(mod) TIMER_CLR_INNER(mod)

#define GPIO_ISR_INNER(port) PORT ## port ## _ISR
#define GPIO_ISR(port) GPIO_ISR_INNER(port)

#define GPIO_VECTOR_INNER(port) PORT ## port ## _VECTOR
#define GPIO_VECTOR(port) GPIO_VECTOR_INNER(port)

#define TIMER_ISR_INNER(timer) TIMER ## timer ## _ISR
#define TIMER_ISR(timer) TIMER_ISR_INNER(timer)

#define TIMER_VECTOR_INNER(type, idx, vect) TIMER ## idx ## _ ## type ## vect ## _VECTOR
#define TIMER_VECTOR(type, idx, vect) TIMER_VECTOR_INNER(type, idx, vect)

#define DCO_FREQ_RANGE_BITS_INNER(r) DCORSEL_ ## r;
#define DCO_FREQ_RANGE_BITS(r) DCO_FREQ_RANGE_BITS_INNER(r)

#define FLL_D_BITS_INNER(d) FLLD_ ## d
#define FLL_D_BITS(d) FLL_D_BITS_INNER(d)

#define FLL_REF_DIV_BITS_INNER(div) FLLREFDIV__ ## div
#define FLL_REF_DIV_BITS(div) FLL_REF_DIV_BITS_INNER(div)

#define CLK_DIV_BITS_INNER(clk, div) DIV ## clk ## __ ## div
#define CLK_DIV_BITS(clk, div) CLK_DIV_BITS_INNER(clk, div)


// Ugly workaround to make the pretty GPIO macro work for OUT register
// (a control bit for TAxCCTLx uses the name 'OUT'): rename to OUT to TAOUT.
enum {
	TAOUT = OUT,
};
#undef OUT

#endif // LIBMSP_PERIPH_H
