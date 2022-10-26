#ifndef VINRO_H
# define VINRO_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>

# define navigation_mode 0
# define edit_mode 1
# define ctrl(k) (k & 0x1f)

typedef struct vinro_conf
{
	char			mode;
	int				c_c;
	int				c_r;
	struct termios	original;
	struct winsize	win;
	char			*to_write;
} vinro_c;

char	*ft_strjoin(char *s1, char *s2, int flag);

#endif
