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
	for (int i = 0; i < screen.y; i++){
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
	xy	tmp;

	std::string	&s = buff[curser.y + scrolls];
	s.insert(curser.x, 1, key);
	tmp.y = curser.y;
	tmp.x = curser.x + 1;
	if (tmp.x >= screen.x){
		tmp.x = 0, tmp.y += 1;
		buff.insert(buff.begin() + scrolls + tmp.y - 1, std::string(""));
		if (tmp.y > screen.y)
			tmp.y -= 1, scrolls += 1;
	}
	init_term();
	wmove(stdscr, tmp.y, tmp.x);
	wrefresh(stdscr);
	return 0;
}

int	_term::rm(){
	getyx(stdscr, curser.y, curser.x);
	int flag = 0;
	unsigned long len = 0;
	if (curser.x == 0 && (scrolls + curser.y != 0)){
		if (buff[curser.y + scrolls - 1].find('\n'))
			buff[curser.y + scrolls - 1].pop_back();
		len = buff[curser.y + scrolls - 1].length();
		std::string tmp(buff[curser.y + scrolls - 1] + buff[curser.y + scrolls]);
		if ((long)tmp.length() > screen.x){
			buff[curser.y + scrolls - 1] = std::string(tmp.begin(), tmp.begin() + screen.x);
			buff[curser.y + scrolls]= std::string(tmp.begin() + screen.x, tmp.end());
		}
		else{
			buff[curser.y + scrolls - 1] = tmp;
			buff.erase(buff.begin() + curser.y + scrolls);
		}
	}
	else if (curser.x != 0){
		buff[curser.y + scrolls].erase(buff[curser.y + scrolls].begin() + curser.x - 1);
		flag = 1;
	}
	init_term();
	wmove(stdscr, curser.y - 1 * (!flag), (curser.x - 1) * flag + len * !flag);
	return 0;
}

int	_term::new_line(){
	getyx(stdscr, curser.y, curser.x);
	char	flag = 0;
	std::string &s = buff[curser.y + scrolls];
	std::string tmp(s.begin() + curser.x, s.end());
	s = std::string(s.begin(), s.begin() + curser.x) + "\n";
	buff.insert(buff.begin() + scrolls + curser.y + 1, tmp);
	if (curser.y == screen.y - 1)
		scrolls++, flag = 1;
	init_term();
	wmove(stdscr, curser.y + 1 * !flag, 0);
	return 0;
}

int	_term::interactive_mode(int key){
	switch (key)
	{
	case 27:
		raw_mode();
		break;
	case KEY_BACKSPACE:
		rm();
		break;
	case 10:
		new_line();
		break;
	case KEY_UP:
		handle_moves('k');
		break;
	case KEY_DOWN:
		handle_moves('j');
		break;
	case KEY_LEFT:
		handle_moves('h');
		break;
	case KEY_RIGHT:
		handle_moves('l');
		break;
	case '\t':
		for (int i = 0; i < TAB_SIZE; i++)
			add(' '), refresh();
		break;
	default:
		if (isprint(key))
			add(key);
		break;
	}
	return 0;
}

int _term::handle_moves(int key){
	getyx(stdscr, curser.y, curser.x);
	if (key == 'h' && (curser.x > 0))
		wmove(stdscr, curser.y, curser.x - 1);
	else if (key == 'l' && (curser.x + 1 < screen.x) \
		&& ((int)(buff[curser.y + scrolls].length() - 1) > (curser.x)))
		wmove(stdscr, curser.y, curser.x + 1);
	else if (key == 'j'){
		if ((curser.y + scrolls) < (long)buff.size() - 1){
			if (curser.y + 1 < screen.y )
				wmove(stdscr, curser.y + 1, 0);
			else
				scrolls++, init_term(), wmove(stdscr, curser.y, 0);
		}
	}
	else if (key == 'k'){
		if (curser.y - 1 >= 0)
			wmove(stdscr, curser.y - 1, 0);
		else if (scrolls > 0)
			scrolls--, init_term(), wmove(stdscr, curser.y, 0);
	}
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
		ft_exit();
		break;
	default:
		if (strchr("hjkl", key))
			handle_moves(key);
		break;
	}
	return 0;
}
