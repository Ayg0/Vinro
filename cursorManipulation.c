#include "vinro.h"
#include <ncurses.h>
#include <stdint.h>

void moveCursor(uint32_t x, uint32_t y){
	if (x == data.maxWidth)
		x = 0, y += 1;
	if (y >= textBuffer.usedRows)
		return ;
	data.cursorPos.x = x;
	if (data.cursorPos.y != y){
		data.cursorPos.y = y;
		currentLine = getRow(data.cursorPos.y);
	}
	if (x > currentLine->size)
		data.cursorPos.x = currentLine->size;
	move(data.cursorPos.y, data.cursorPos.x);
}