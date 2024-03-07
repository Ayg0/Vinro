#include "vinro.h"
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>

void	handleControlInput(int c){
	switch (c) {
		case 'q':
			_CLOSE_WINDOW = 1, SET_FIELD(data.attr.fileOptions, SAVE_EXIT);
			break;
		case KEY_UP:
			moveCursor(data.cursorPos.x, data.cursorPos.y - 1);
			break;
		case KEY_DOWN:
			moveCursor(data.cursorPos.x, data.cursorPos.y + 1);
			break;
		case KEY_LEFT:
			moveCursor(data.cursorPos.x - 1, data.cursorPos.y);
			break;
		case KEY_RIGHT:
			moveCursor(data.cursorPos.x + 1, data.cursorPos.y);
			break;
		case 'e':
			data.mode = EDIT_MODE;
			break;
		case ':':
			getFullCommand();
		default:
			break;
	}
}

void	handleEditInput(int c){
	uint8_t insertionTimes = 1;
	switch (c) {
		case KEY_ESC:
			data.mode = CONTROL_MODE;
			break;
		case KEY_BACKSPACE:
			deleteCharacter();
			break;
		case KEY_UP:
			moveCursor(data.cursorPos.x, data.cursorPos.y - 1);
			break;
		case KEY_DOWN:
			moveCursor(data.cursorPos.x, data.cursorPos.y + 1);
			break;
		case KEY_LEFT:
			moveCursor(data.cursorPos.x - 1, data.cursorPos.y);
			break;
		case KEY_RIGHT:
			moveCursor(data.cursorPos.x + 1, data.cursorPos.y);
			break;
		case '\n':
			enter();
			break;
		default:
			if (c == '\t')
				c = ' ', insertionTimes = data.attr.tabSize;
			for (uint8_t i = 0; i < insertionTimes; i++)
				insertCharacter(currentLine, c, data.cursorPos.x, data.cursorPos.y);
	}	
}

void updateInfoBuffer(){
	char *modes[] = {"  EDIT  ", " CONTROL"};
	sprintf(data.infoBuffer, "-- %s MODE  --    C:%d, R:%d", modes[data.mode],
			data.cursorPos.x, data.cursorPos.y);
}