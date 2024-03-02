
#include "vinro.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern vinroData data;
extern buffer textBuffer;

uint8_t addRows(){
	uint32_t nextSize = textBuffer.nbRows * 2;

	if (!nextSize)
		nextSize = 2;
	textBuffer.lines = realloc(textBuffer.lines, nextSize * sizeof(lineData));
	if (textBuffer.lines == NULL)
		displayError("Allocation Failed");
	textBuffer.nbRows =  nextSize;
	return 0;
}

uint8_t appendRow(char *line, uint32_t lineSize, uint32_t atRow){
	if (atRow >= textBuffer.nbRows)
		addRows();
	lineData *linePtr = &textBuffer.lines[atRow];

	linePtr->line = calloc(lineSize + 1, sizeof(char));
	if (!linePtr->line)
		displayError("Allocation Failed");
	linePtr->size = lineSize;
	memcpy(linePtr->line, line, lineSize);
	textBuffer.usedRows++;
	return 0;
}