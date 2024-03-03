
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
	lineData *line = malloc(sizeof(lineData));
	if (!line)
		displayError("Allocation Failed");

	if (atIndex != 0){
		line->prev = getRow(atIndex - 1);
		line->prev->next = line;
	}
	else
	 	textBuffer.lines = line;
	line->next = getRow(atIndex + 1);
	if (line->next == NULL)
		textBuffer.end = line;
	textBuffer.nbRows++;
	return line;
}

uint8_t appendRow(char *line, uint32_t lineSize, uint32_t atRow){
	lineData *linePtr = NULL;
	if (atRow >= textBuffer.nbRows)
		linePtr = addRows(atRow);
	else
		linePtr = getRow(atRow);

	linePtr->line = calloc(lineSize + 1, sizeof(char));
	if (!linePtr->line)
		displayError("Allocation Failed");
	linePtr->size = lineSize;
	memcpy(linePtr->line, line, lineSize);
	textBuffer.usedRows++;
	return 0;
}