#include "macros.h"
#include "vinro.h"
#include <ncurses.h>
#include <stdint.h>
#include <strings.h>

void proccessCommand(){
	if (data.infoBuffer[1] == '!')
		_CLOSE_WINDOW = 1;
	else if (data.infoBuffer[1] == 'q'){
		SET_FIELD(data.attr.fileOptions, SAVE_EXIT);
		_CLOSE_WINDOW = 1;
	}
	else if (data.infoBuffer[1] == 'w'){
		SET_FIELD(data.attr.fileOptions, SAVE_EXIT);
		saveData(data.fileToSave);
		RESET_FIELD(data.attr.fileOptions, SAVE_EXIT);
	}
}

void deleteFromBuff(uint32_t *i){
	if (*i <= 1)
		return;
	data.infoBuffer[*i - 1] = '\0'; 
	(*i)--;
	return ;
}

void	getFullCommand(){
	int32_t c;
	uint32_t i = 1;

	bzero(data.infoBuffer, data.maxWidth);
	data.infoBuffer[0] = ':';
	clearLine(data.maxHeight);
	mvprintw(data.maxHeight, 0, "%s", data.infoBuffer);
	while (1) {
		if (i == data.maxWidth)
			break;
		c = getch();
		switch (c) {
			case ERR:
				continue ;
			case KEY_ESC:
				return ;
			case '\n':
				return proccessCommand();
			case KEY_BACKSPACE:
				deleteFromBuff(&i);
				clearLine(data.maxHeight);
				break;
			default:
				data.infoBuffer[i] = c;
				i++;
		}
		mvprintw(data.maxHeight, 0, "%s", data.infoBuffer);
	}
}