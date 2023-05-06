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
	for (size_t i = 0; i < len; i++)
		waddch(stdscr, buff[start][i]);
	waddch(stdscr, '\n');
	return 0;
}

int	_term::init_term(){
	size_t	w = scrolls;
	wmove(stdscr, 0, 0);
	for (size_t i = 0; i < screen.y; i++){
		if (w < buff.size()){
			print_line(w);
			w++;
		}
		else{
			waddch(stdscr, '~');
			waddch(stdscr, '\n');
		}
	}
	wmove(stdscr, 0, 0);
	wrefresh(stdscr);
	return 2;
}

int	_term::add(int key){
	getyx(stdscr, curser.y, curser.x);
	if (isprint(key)){
		buff[curser.y + scrolls].insert(curser.x, 1, key);
		init_term();
	}
	return 0;
}

int	_term::rm(){
	getyx(stdscr, curser.y, curser.x);
	return 0;
}


int	_term::interactive_mode(int key){
	if (key == 27)
		return (raw_mode());
	else if (key == 127)
		return (rm());
	add(key);
	init_term();
	return 0;
}

int	_term::where_to_go(std::vector<std::string> &buff, int y, int x, int to_go, int &flag){
	if (y + scrolls + to_go > buff.size()){
		buff.push_back(" ");
		flag = 1;
		return 0;
	}
	else if (x > buff[y + scrolls + to_go].length()){
		return (buff[y + scrolls + to_go].length() - 1);
	}
	else
		return (x);
}

int _term::handle_moves(int key){
	int	i = 1 * (key == 'j') + -1 * (key == 'k');
	getyx(stdscr, curser.y, curser.x);
	if (key == 'h' && (curser.x > 0))
		wmove(stdscr, curser.y, curser.x - 1);
	else if (key == 'l' && (curser.x + 1 < screen.x - 1) \
		&& (buff[curser.y + scrolls].length() > curser.x))
		wmove(stdscr, curser.y, curser.x + 1);
	else if ((curser.y + i < screen.y) && (curser.y + i >= 0)){
		int flag = 0, x = where_to_go(buff, curser.y, curser.x, i, flag);
		if (flag)
			init_term();
		wmove(stdscr,curser.y + i, x);
	}
	else
		scrolls += i * ((scrolls + i) >= 0);
	return (0);
}

int	_term::view_mode(int key, _file_D &f){
	switch (key)
	{
	case 'i':
		edit_mode();
		break;
	case 'w':
		f.write_file(*this);
		exit(0);
		break;
	default:
		if (strchr("hjkl", key))
			handle_moves(key);
		break;
	}
	return 0;
}
