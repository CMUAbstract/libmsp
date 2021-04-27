#ifndef _LIBMSP_MEM_H
#define _LIBMSP_MEM_H

/* The linker script needs to allocate these sections into FRAM region. */
#define __ro_nv __attribute__((section(".ro_nv_vars")))

// This is the switch we have to flip to compile into the section of memory
// reachable with 16 bits
#ifndef LIBMSP_NO_MLARGE
#define __nv    __attribute__((section(".upper.rodata")))
#else
#warning "Running persistent!"
#define __nv    __attribute__((section(".persistent")))
#endif

#define __fram __attribute__((section(".persistent")))
#define __ro_fram __attribute__((section(".rodata")))
#define __hifram __attribute__((section(".upper.persistent")))
#define __ro_hifram __attribute__((section(".upper.rodata")))
#define __known __attribute__((section(".known")))

#endif // _LIBMSP_MEM_H
