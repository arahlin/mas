/***************************************************
  mcecmd.h - header file for MCE API

  Matthew Hasselfield, 07.06.11

***************************************************/

#ifndef _MCECMD_H_
#define _MCECMD_H_

/*! \file mcecmd.h
 *  \brief Header file for libmce
 *
 *  Projects linking to libmce should include this header file.
 */

/* mce.h defines the structures used by the dsp driver */

#include <mce.h>
#include <mce_errors.h>

/*! \def MCE_SHORT
 *  \brief Length of short strings.
 */

#define MCE_SHORT 32


/*! \def MCE_LONG
 *  \brief Length of long strings.
 */

#define MCE_LONG 1024


/*! \def MAX_CONS
 *  \brief Number of MCE handles available
 */

#define MAX_CONS 16


/*
   API: all functions return a negative error value on failure.  On
   success, the return value is 0.

   Begin a session by calling mce_open.  The return value is the
   handle that must be used in subsequent calls.  Connections should
   be closed when a session is finished.
*/

int mce_open(char *dev_name);
int mce_close(int handle);


/* MCE user commands - these are as simple as they look */

int mce_start_application(int handle, int card_id, int para_id);
int mce_stop_application(int handle, int card_id, int para_id);
int mce_reset(int handle, int card_id, int para_id);

int mce_write_block(int handle, int card_id, int para_id,
		    int n_data, const u32 *data);
int mce_read_block(int handle, int card_id, int para_id,
		   int n_data, u32 *data, int n_cards);


/* MCE special commands - these provide additional logical support */

int mce_write_element(int handle, int card_id, int para_id,
		      int data_index, u32 datum);

int mce_read_element(int handle, int card_id, int para_id,
		     int data_index, u32 *datum);

int mce_write_block_check(int handle, int card_id, int para_id,
			  int n_data, const u32 *data, int checks);


/* Raw i/o routines; roll your own packets */

int mce_send_command_now(int handle, mce_command *cmd);
int mce_read_reply_now(int handle, mce_reply *rep);
int mce_send_command(int handle, mce_command *cmd, mce_reply *rep);


/* Useful things... */

u32 mce_checksum( const u32 *data, int count );
u32 mce_cmd_checksum( const mce_command *cmd );
int mce_cmd_match_rep( const mce_command *cmd, const mce_reply *rep );


/* Perhaps you are a human */

char *mce_error_string(int error);



#endif
