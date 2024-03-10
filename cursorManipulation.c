#include "vinro.h"
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>

int32_t	textScroll(uint8_t up){
	int32_t y = 0;
	if (up && textBuffer.start->prev){
		textBuffer.startRowIndex--;
		textBuffer.start = textBuffer.start->prev;
	}
	else if (!up && textBuffer.start->next){
		textBuffer.start = textBuffer.start->next;
		textBuffer.startRowIndex++;
		y = data.maxHeight - 1;
	}
	return y;
}

void	moveCursor(int32_t x, int32_t y){

	if (y == -1 || (y == (int32_t)data.maxHeight
			&& y + textBuffer.startRowIndex < textBuffer.nbRows))
		y = textScroll(y == -1);
	if ((uint32_t)x == data.maxWidth)
		x = 0, y += 1;
	if ((uint32_t)y + textBuffer.startRowIndex >= textBuffer.nbRows || x < 0)
		return ;
	data.cursorPos.x = x;
	data.cursorPos.y = y;
	currentLine = getRow(data.cursorPos.y + textBuffer.startRowIndex);
	if ((uint32_t)x > currentLine->size)
		data.cursorPos.x = currentLine->size;
	move(data.cursorPos.y, data.cursorPos.x);
}