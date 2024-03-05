#include "vinro.h"
#include <ncurses.h>
#include <stdint.h>

void moveCursor(int32_t x, int32_t y){
	if (x == data.maxWidth){
		x = 0;
		y += 1;
	}
	move(y, x);
	data.cursorPos.x = x;
	if (data.cursorPos.y != (uint32_t)y){
		data.cursorPos.y = y;
		currentLine = getRow(data.cursorPos.y);
	}
}