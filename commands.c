#include "vinro.h"
#include <ncurses.h>
#include <stdint.h>
#include <strings.h>

void proccessCommand(){
	if (data.infoBuffer[1] == '!'){
		_CLOSE_WINDOW = 1;
	}
}

void	getFullCommand(){
	int32_t c;
	uint32_t i = 1;

	bzero(data.infoBuffer, data.maxWidth);
	data.infoBuffer[0] = ':';
	clearLine(data.maxHeight);
	mvprintw(data.maxHeight, 0, "%s", data.infoBuffer);
	while (1) {
		c = getch();
		if (c == ERR)
			continue;
		if (i == data.maxWidth || c == KEY_ESC)
			return;
		if (c == '\n')
			return proccessCommand();
		data.infoBuffer[i] = c;
		mvprintw(data.maxHeight, 0, "%s", data.infoBuffer);
		i++;
	}
}