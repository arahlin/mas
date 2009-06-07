#ifndef _DSP_IOCTL_H_
#define _DSP_IOCTL_H_

#include <linux/ioctl.h>

/* IOCTL stuff */

#define DSPDEV_IOC_MAGIC 'p'
#define DSPDEV_IOCT_RESET  _IO(DSPDEV_IOC_MAGIC,  0)
#define DSPDEV_IOCT_SPEAK  _IO(DSPDEV_IOC_MAGIC,  1)
#define DSPDEV_IOCT_ERROR  _IO(DSPDEV_IOC_MAGIC,  2)
#define DSPDEV_IOCT_CORE   _IO(DSPDEV_IOC_MAGIC,  3)
/*#define DSPDEV_IOCT_CORE_IRQ _IO(DSPDEV_IOC_MAGIC, 4)*/

#endif
