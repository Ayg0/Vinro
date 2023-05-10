#include "vinro.hpp"

int	_term::init_vars(){
	getmaxyx(stdscr, screen.y, screen.x);
	flags = 0;
	edit_mode();
	scrolls = 0;
	return 0;
}

std::vector<std::string>	&_term::g_buff(){
	return (buff);
}

xy			_term::get_sreen() const{
	return (screen);
}

int	_term::raw_mode(){
	flags &= ~EDIT_MASK;
	return 0;
}

int	_term::edit_mode(){
	flags |= EDIT_MASK;
	return 0;
}

int	_term::print_line(size_t start){
	size_t len = buff[start].length();
	size_t i;
	for (i = 0; i < len; i++)
		waddch(stdscr, buff[start][i]);
	if (buff[start][i - 1] != '\n')
		waddch(stdscr, '\n');
	return 0;
}

int	_term::init_term(){
	size_t	w = scrolls;
	wmove(stdscr, 0, 0);
	for (int i = 0; i < (screen.y - 1); i++){
		if (w < buff.size())
			print_line(w++);
		else
			printw("~\n");
	}
	wmove(stdscr, 0, 0);
	refresh();
	return 2;
}



