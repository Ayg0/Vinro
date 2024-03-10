#include "vinro.h"
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

void	insertCharacter(lineData *thisLine, char c, int32_t x, int32_t y){
	int justReccursionFlag = 0;

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
			if (data.cursorPos.x != data.maxWidth - 1){
				insertCharacter(thisLine->next, thisLine->line[thisLine->size - 1], -1, y + 1);
				thisLine->line[thisLine->size - 1] = 0;
				thisLine->size--;
			}
			else
				return insertCharacter(thisLine->next, c, 0, y + 1);
		}
	}
	if (x == -1)
		justReccursionFlag = 1, x = 0;
	for (int32_t i = thisLine->size; i > x; i--)
		thisLine->line[i] = thisLine->line[i - 1];
	thisLine->line[x] = c;
	thisLine->size++;
	if (!justReccursionFlag)
		moveCursor(x + 1, y);
}

void splitLine(lineData *originline, lineData *next, int32_t index){
	strncpy(next->line, originline->line + index, originline->size - index);
	next->size = originline->size - index;
	originline->line[index] = 0;
	bzero(originline->line + index, originline->size - index);
	originline->size = index;
}

void enter(){
	currentLine->hadNewLine = 1;
	appendRow("", 0, data.cursorPos.y + 1, 0);
	splitLine(currentLine, currentLine->next, data.cursorPos.x);
	moveCursor(0, data.cursorPos.y + 1);
}

void removeLine(lineData *line){
	if (line->prev)
		line->prev->next = line->next;
	else
		textBuffer.lines = line->next;
	if (line->next)
		line->next->prev = line->prev;
	currentLine = line->prev;
	free(line->line);
	free(line);
	textBuffer.nbRows--;
}

void appendToPrevRow(lineData *currentLine){
	int32_t x, y, i, j = 0;

	lineData *prevLine;

	if (!currentLine->prev)
			return;
	prevLine = currentLine->prev;
	x = prevLine->size;
	y = data.cursorPos.y - 1;
	i = prevLine->size;
	while (i < (int32_t)data.maxWidth && j < (int32_t)currentLine->size) {
		prevLine->line[i] = currentLine->line[j];
		i++, j++;
	}
	prevLine->size = i;
	if (prevLine->size == data.maxWidth - 1)
		prevLine->hadNewLine = 0;
	strcpy(currentLine->line, currentLine->line + j);
	currentLine->size = currentLine->size - j;
	if (currentLine->size == 0)
		removeLine(currentLine);
	moveCursor(x, y);
}

void deleteCharacter(){

	if (data.cursorPos.x == 0)
		return appendToPrevRow(currentLine);
	for (uint32_t i = data.cursorPos.x - 1; i < currentLine->size; i++)
		currentLine->line[i] = currentLine->line[i + 1];
	if (!currentLine->hadNewLine && currentLine->next){
		currentLine->line[currentLine->size - 1] = currentLine->next->line[0];
		strcpy(currentLine->next->line, currentLine->next->line + 1);
		currentLine->next->size--;
		if (currentLine->next->size == 0)
			removeLine(currentLine->next);
	}
	else{
		currentLine->line[currentLine->size] = '\0';
		currentLine->size--;
	}
	data.cursorPos.x--;
}

void	clearLine(int32_t index){
	char line[data.maxWidth];
	for (uint32_t i = 0; i < data.maxWidth - 1; i++)
		line[i] = ' ';
	line[data.maxWidth - 1] = 0;
	mvprintw(index, 0, "%s", line);
}