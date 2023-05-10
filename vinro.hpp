#ifndef VINRO_HPP
# define VINRO_HPP

# include <iostream>
# include <ncurses.h>
# include <termios.h>
# include <string.h>
# include <fstream>
# include <cstdlib>
# include <vector>
# include <unistd.h>

# if __APPLE__
	# define BACKSPACE 127
# else
	# define BACKSPACE KEY_BACKSPACE
# endif

# define EDIT_MASK 2
# define TAB_SIZE 2

typedef	struct _xy{
	int	x;
	int	y;
} xy;

class _term{
public:
	int			flags;
	long		scrolls;
	xy			screen;
	xy			curser;
	std::vector<std::string> buff;

	int	init_vars();
	int	init_term();
	int	raw_mode();
	int	edit_mode();
	int	view_mode(int key, class _file_D &f);
	int	interactive_mode(int key);
	int	add(int key);
	int	rm();
	int	new_line();
	int handle_moves(int key);
	int	where_to_go(std::vector<std::string> &buff, int y, int x, int to_go, int &flag);
	std::vector<std::string>	&g_buff();
	xy			get_sreen() const;
	int	print_line(size_t start);
};

class _file_D{
	std::string	file_name;
public:
	_file_D(char *name){
		file_name = std::string(name);
	}
	int	read_file(_term &Inf);
	int	write_file(_term &Inf);
};

void	ft_exit();

#endif