#ifndef VINRO_H
# define VINRO_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <errno.h>
#include <stdio.h>

# define ctrl(k) (k & 0x1f)

typedef struct vinro_conf
{
	struct termios	original;
	struct winsize	win;
} vinro_c;


#endif
