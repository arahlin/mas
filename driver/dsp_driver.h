#ifndef _DSP_DRIVER_H_
#define _DSP_DRIVER_H_

#include "mce/dsp.h"
#include "mce/dsp_errors.h"

#ifdef FAKEMCE
#  include <dsp_fake.h>
#else
#  include "dsp_pci.h"
#endif

#define DSPDEV_NAME "mce_dsp"
#define DSP_DEFAULT_TIMEOUT (HZ*50/100)

/* DSP code versions */

#define DSP_U0103          0x550103
#define DSP_U0104          0x550104
#define DSP_U0105          0x550105

typedef int (*dsp_callback)(int, dsp_message*, int);

typedef int (*dsp_handler)(dsp_message *, unsigned long data);

/* Prototypes */

int dsp_send_command(dsp_command *cmd, dsp_callback callback,
		     int card);

int dsp_send_command_wait(dsp_command *cmd, dsp_message *msg,
			  int card);

void dsp_clear_RP(void);

int dsp_driver_ioctl(unsigned int iocmd, unsigned long arg, int card);

int dsp_proc(char *buf, int count, int card);

int dsp_int_handler(dsp_message *msg, int card);

int dsp_set_handler(u32 code, dsp_handler handler, unsigned long data,
		    int card);

int dsp_clear_handler(u32 code, int card);

int dsp_driver_probe(int card);

void dsp_driver_remove(int card);

#endif
