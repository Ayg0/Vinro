#include "vinro.h"

vinro_c	term;

void	error_what(char *s)
{
	perror(s);
	exit(1);
}

void	get_window_size()
{
	if (ioctl(1, TIOCGWINSZ, &term.win)  == -1 || term.win.ws_col == 0)
		error_what("window size");
}

void	enable_raw()
{
	struct termios	termi;

	termi = term.original;
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
	write(1, "\033[2J\033[H\n", 7);
	if (tcsetattr(1, TCSAFLUSH, &term.original) == -1)
		error_what("tcsetattr");
}

void	draw_first_lines()
{
	int	i;

	i = 0;
	while (i < term.win.ws_col)
	{
		write(1, "~", 1);
		(i != term.win.ws_col - 1) && write(1, "\r\n", 2);
		i++;
	}
	write(1, "\033[H", 3);
}

void	refrech()
{
	write(1, "\033[2J\033[H", 7);
	draw_first_lines();
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
	write(1, &c, 1);
}

void	init_vinro()
{
	tcgetattr(1, &term.original);
	get_window_size();
}

int	main()
{
	init_vinro();
	enable_raw();
	atexit(disable_raw);
	while (1)
	{
		refrech();
		get_key_press();
	}
}
