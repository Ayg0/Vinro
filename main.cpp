#include <iostream>
#include <ncurses.h>
#include <termios.h>

typedef	struct _pos{
	int	x;
	int	y;
} pos;

class _term{
	int		flags;
	pos		curser;
	std::string	buff;

	public:
	int	init_term();
	int	raw_mode();
	int	edit_mode();
	int	add();
	int	rm();
	int	mv_cursor();
	int	
};



int	main(){
	initscr();
	cbreak();
	noecho();
	// keypad(stdscr, TRUE);
	int h, w;
	getmaxyx(stdscr, h, w);
	wmove(stdscr, 0, 0);
	waddch(stdscr, 'a');
	wrefresh(stdscr);
	endwin();
	return (0);
}
