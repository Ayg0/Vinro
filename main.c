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
		term.to_write = ft_strjoin(term.to_write, "~", -2);
		term.to_write = ft_strjoin(term.to_write, "\033[k", -2);
		(i != term.win.ws_col - 1)
			&& (term.to_write = ft_strjoin(term.to_write, "\r\n", -2));
		i++;
	}
	//term.to_write = ft_strjoin(term.to_write, "\033[H", -2);
}

void	refrech()
{
	char	s[12];
	term.to_write = ft_strjoin(term.to_write, "\033[H", -2);
	draw_first_lines();
	sprintf(s, "\033[%d;%dH", term.c_r, term.c_c);
	term.to_write = ft_strjoin(term.to_write, s, -2);
	write(1, term.to_write, strlen(term.to_write));
	free(term.to_write);
	term.to_write = NULL;
}

void	wait_until_key(char *c)
{
	int	re;

	while ((re = read(1, c, 1)) != 1)
		if (re == -1 && errno != EAGAIN) // just try again it's okay
			error_what("read");
}

void	what_to_do(char c)
{
	if (term.mode == navigation_mode)
	{
		term.c_c += 1 * (c == 'd' && (term.c_c < term.win.ws_col)) - 1 * (c == 'a' && (term.c_c));
		term.c_r += 1 * (c == 's' && (term.c_r < term.win.ws_row)) - 1 * (c == 'w' && (term.c_r));
	}
	term.mode += (term.mode == edit_mode && c == 27) * -1
		+ (term.mode == navigation_mode && c == 27) * 1;
	if (c == ctrl('q'))
		exit (0);

}

void	get_key_press()
{
	char	c = '\0';

	wait_until_key(&c);
	what_to_do(c);
	write(1, &c, 1);
}

void	init_vinro()
{
	term.mode = navigation_mode;
	term.c_c = 0;
	term.c_r = 0;
	term.to_write = NULL;
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
