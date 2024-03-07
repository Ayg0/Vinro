#ifndef MACROS_H
# define MACROS_H

#define KEY_ESC 27
// OPTION FOR FILE MANIPULATION
# define SAVE_EXIT		(1 << 0) // save on exit
# define XXXX_OPT		(1 << 1)
# define XXXY_OPT		(1 << 2)
# define XXYX_OPT		(1 << 3)
# define XXYY_OPT		(1 << 4)
# define XYXX_OPT		(1 << 5)
# define XYXY_OPT		(1 << 6)
# define XYYY_OPT		(1 << 7)
# define SET_FIELD(SR, REQ) 	(SR = SR | (REQ))
# define RESET_FIELD(SR, REQ) 	(SR = SR & ~(REQ))
# define IS_SET(SR, REQ)		((SR & (REQ)) == (REQ))
#endif