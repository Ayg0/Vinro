
#include "vinro.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern vinroData 	data;
extern buffer 		textBuffer;


lineData *getRow(uint32_t index){
	uint32_t i = 0;
	lineData *tmp = NULL;

	tmp = textBuffer.lines;
	while (i < index && tmp != NULL) {
		tmp = tmp->next;
		i++;		
	}
	return  tmp;
}

lineData *addRows(uint32_t atIndex){
	lineData *line = calloc(1, sizeof(lineData));
	if (!line)
		displayError("Allocation Failed");

	if (atIndex != 0){
		line->prev = getRow(atIndex - 1);
		lineData *tmp = line->prev->next;
		line->prev->next = line;
		line->next = tmp;
	}
	else
	 	textBuffer.lines = line;
	line->next = getRow(atIndex + 1);
	if (line->next == NULL)
		textBuffer.end = line;
	textBuffer.nbRows++;
	return line;
}

uint8_t 	copyline(lineData *to, char const *from, uint32_t len, uint8_t hadNewLine){
	static char *line;
	uint32_t i = 0, j = 0;
	const char *end = &from[len];
	if (!line)
		line = calloc(data.maxWidth, sizeof(char));
	while (line[i]) {
		to->line[i] = line[i];
		i++;
	}
	if (!hadNewLine && !_DONT_IGNORE)
		end = strrchr(from, ' ');
	while (i < data.maxWidth && from[j]) {
		if (end == &from[j])
			break;
		to->line[i] = from[j];
		i++, j++;
	}
	i = 0;
	while(from[j]){
		line[i] = from[j];
		i++, j++;
	}
	line[i] = 0;
	return 0;
}

uint8_t appendRow(char *line, uint32_t lineSize, uint32_t atRow, uint8_t hadNewLine){
	lineData *linePtr = NULL;
	
	atRow += textBuffer.startRowIndex;
	linePtr = addRows(atRow);
	linePtr->line = calloc(data.maxWidth, sizeof(char));
	if (!linePtr->line)
		displayError("Allocation Failed");
	linePtr->size = lineSize;
	copyline(linePtr, line, lineSize, hadNewLine);
	linePtr->hadNewLine = hadNewLine;
	return 0;
}