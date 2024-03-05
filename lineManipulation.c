#include "vinro.h"
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	insertCharacter(lineData *thisLine, int c, uint32_t x, int y, uint8_t updateFlag){

	if (thisLine->size == (uint32_t)data.maxWidth - 1){
		if (thisLine->hadNewLine){
			thisLine->hadNewLine = 0;
			char *line = calloc(data.maxWidth, sizeof(char));
			thisLine->size -= 1;
			appendRow(line, 1, data.cursorPos.y + 1, 1);
			free(line);
		}
		else{
			if (!thisLine->next)
				appendRow("", 0, y + 1, 0);
			return insertCharacter(thisLine->next, thisLine->line[thisLine->size - 1], 0, y + 1, 1);
		}
	}
	for (uint32_t i = thisLine->size; i > x; i--)
		thisLine->line[i] = thisLine->line[i - 1];
	thisLine->line[x] = c;
	thisLine->size++;
	if (updateFlag)
		moveCursor(data.cursorPos.x + 1, data.cursorPos.y);
}

void enter(){
	currentLine->hadNewLine = 1;
	appendRow("", 0, data.cursorPos.y + 1, 1);
	moveCursor(0, data.cursorPos.y + 1);
}

void deleteCharacter(){
	if (data.cursorPos.x == 0)
		return ;
	for (uint32_t i = data.cursorPos.x - 1; i < currentLine->size; i++)
		currentLine->line[i] = currentLine->line[i + 1];
	currentLine->line[currentLine->size] = '\0'; 
	data.cursorPos.x--;
	currentLine->size--;
}