#include "vinro.hpp"

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

int	_term::ft_erase(){
	xy tmp;

	getyx(stdscr, tmp.y, tmp.x);
	buff.erase(buff.begin() + tmp.y + scrolls);
	if (tmp.y != 0)
		tmp.y--;
	if (!buff.size())
		buff.push_back("\n");
	init_term();
	wmove(stdscr, tmp.y, tmp.x);
	return (0);
}

int	_term::string_command(_file_D &f){
	std::string cmd;
	int	key = 0, index = 0;
	while (key != '\n'){
		if ((key = getch()) == ERR)
			continue;
		else if (isprint(key))
			cmd.insert(index++, 1, key);
	}
	if (cmd == "wq"){
		f.write_file( *this );
		ft_exit();
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
		break;
	case 'q':
		ft_exit();
		break;
	case 'd':
		ft_erase();
		break;
	case '\n':
		string_command(f);
	default:
		if (strchr("hjkl", key))
			handle_moves(key);
		break;
	}
	return 0;
}