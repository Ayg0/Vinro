#include "vinro.h"
#include <ncurses.h>

void	handleControlInput(int c){
	switch (c) {
		case 'q':
			_CLOSE_WINDOW = 1;
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
	}
}

void	handleEditInput(int c){
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
				c = ' ';
			insertCharacter(currentLine, c, data.cursorPos.x, data.cursorPos.y);
	}	
}