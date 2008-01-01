#ifndef _MCE_DRIVER_H
#define _MCE_DRIVER_H

#include "kversion.h"
#include <dsp.h>
#include <mce.h>


#define MCEDEV_NAME "mce_cmd"
#define MCEDATA_NAME "mce_data"

#define MCE_DEFAULT_TIMEOUT (HZ*100/100)

typedef int (*mce_callback)(int err, mce_reply* rep);


int mce_init_module(int dsp_version);

int mce_cleanup(void);

int mce_proc(char *buf, int count);

int mce_error_register( void );

void mce_error_reset( void );

int mce_send_command_user( __user mce_command *cmd,
			   mce_callback callback );

int mce_send_command( mce_command *cmd,
		      mce_callback callback,
		      int nonblock );

int mce_get_reply( __user void* reply_user,
		   void* reply_kern, int count );

int mce_clear_commflags(void);

int mce_interface_reset(void);

int mce_hardware_reset(void);

#endif
