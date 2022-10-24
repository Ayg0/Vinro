#include "vinro.h"

struct termios original;

void	error_what(char *s)
{
	perror(s);
	exit(1);
}

void	enable_raw()
{
	struct termios	termi;

	termi = original;
	termi.c_iflag &= ~(IXON | ICRNL);
	termi.c_oflag &= ~(OPOST);
	termi.c_lflag &= ~ (ECHO | ICANON | ISIG | IEXTEN);
  	termi.c_cc[VMIN] = 0;
  	termi.c_cc[VTIME] = 1;
	if (tcsetattr(1, TCSAFLUSH, &termi) == -1)
		error_what("tcsetattr");
}

void	disable_raw()
{
	if (tcsetattr(1, TCSAFLUSH, &original) == -1)
		error_what("tcsetattr");
}

void	refrech()
{
	write(1, "\033[2J\033[H", 4);
}

void	wait_until_key(char *c)
{
	int	re;

	while ((re = read(1, c, 1)) != 1)
		if (re == -1 && errno != EAGAIN) // just try again it's okay
			error_what("read");
}

void	get_key_press()
{
	char	c = '\0';
	int		re;

	wait_until_key(&c);
	if (c == ctrl('q'))
		exit (0);
//	write(1, &c, 1);
}

int	main()
{

	tcgetattr(1, &original);
	enable_raw();
	atexit(disable_raw);
	while (1)
	{
		refrech();
		get_key_press();
	}
}
