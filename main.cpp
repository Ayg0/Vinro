#include "vinro.hpp"

int	init_ncurses(){
	initscr();
	noecho();
	cbreak();
	nodelay(stdscr, TRUE);
	return 0;
}

int	main(int ac, char **av){
	if (ac != 2){
		std::cout << "Usage ./vinro filename." << std::endl;
		return 1;
	}
	_term 	win;
	_file_D file(av[1]);
	int		key;

	init_ncurses();
	win.init_vars();
	file.read_file(win);
	win.init_term();
	while (1){
		if ((key = getch()) == ERR)
			continue;
		else{
			if (win.flags & EDIT_MASK)
				win.interactive_mode(key);
			else
				win.view_mode(key, file);
			refresh();
		}
	}
	return (0);
}
//
