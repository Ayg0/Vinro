#include "vinro.h"
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>

void moveCursor(int32_t x, int32_t y){
	if ((uint32_t)x == data.maxWidth)
		x = 0, y += 1;
	if ((uint32_t)y >= textBuffer.usedRows || x < 0)
		return ;
	data.cursorPos.x = x;
	if (data.cursorPos.y != (uint32_t)y){
		data.cursorPos.y = y;
		currentLine = getRow(data.cursorPos.y);
	}
	if ((uint32_t)x > currentLine->size)
		data.cursorPos.x = currentLine->size;
	move(data.cursorPos.y, data.cursorPos.x);
}