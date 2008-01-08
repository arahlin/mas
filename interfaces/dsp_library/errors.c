#include "dsp_errors.h"

char *dsp_error_string(int error)
{
	switch (-error) {
	case DSP_ERR_FAILURE:
		return "DSP replied with ERROR.";

	case DSP_ERR_HANDLE:
		return "Bad dsp_library handle.";

	case DSP_ERR_DEVICE:
		return "I/O error on driver device file.";

	case DSP_ERR_FORMAT:
		return "Bad packet structure.";

	case DSP_ERR_REPLY:
		return "Reply does not match command.";

	case DSP_ERR_BOUNDS:
		return "Data size is out of bounds.";

	case DSP_ERR_CHKSUM:
		return "Checksum failure.";

	case DSP_ERR_KERNEL:
		return "Driver failed on routine kernel call.";

	case DSP_ERR_IO:
		return "I/O error in DSP communication.";

	case DSP_ERR_STATE:
		return "Unexpected DSP driver state.";

	case DSP_ERR_MEMTYPE:
		return "Invalid memory type.";

	case DSP_ERR_TIMEOUT:
		return "Timed-out waiting for DSP reply.";

	case 0:
		return "Success.";
	}

	return "Unknown dsp_library error.";
}