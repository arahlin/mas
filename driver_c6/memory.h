/* -*- mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*-
 *      vim: sw=8 ts=8 et tw=80
 */
#ifndef _MAS_MEMORY_H_
#define _MAS_MEMORY_H_


#ifdef FAKEMCE
# include <dsp_fake.h>
#else
# include "dsp_driver.h"
#endif

// Ensure that address alignment is configured

#ifndef DMA_ADDR_ALIGN
# define DMA_ADDR_ALIGN 1024
# define DMA_ADDR_MASK (0xffffffff ^ (DMA_ADDR_ALIGN-1))
#endif




#endif