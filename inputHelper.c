#include "vinro.h"
#include <ncurses.h>

void	handleControlInput(int c){
	switch (c) {
		case 'q':
			_CLOSE_WINDOW = 1;
			break;
		case KEY_UP:
			break;
		case KEY_DOWN:
			break;
		case KEY_LEFT:
			break;
		case KEY_RIGHT:
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
		case '\n':
			enter();
			break;
		default:
			insertCharacter(currentLine, c, data.cursorPos.x, data.cursorPos.y);
	}	
}