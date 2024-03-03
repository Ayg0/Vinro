#include "vinro.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t mystrlen(char *line, uint8_t *hadNewLine){
	uint32_t i = 0;

	while (line[i]) {
		if (line[i] == '\r' || line[i] == '\n')
			*hadNewLine = 1;
		i++;
	}
	if (feof(file))
		_DONT_IGNORE = 1;
	return i;
}

void loadData(char *fileName){
	char line[data.maxWidth];
	uint8_t hadNewLine;
	uint32_t i = 0, lineSize = 0;

	file = fopen(fileName, "a+");
	if (!file)
		displayError("File \?\?!");
	rewind(file);
	while (fgets(line, sizeof(line), file) != NULL) {
		hadNewLine = 0;
		lineSize = mystrlen(line, &hadNewLine);
        appendRow(line, lineSize, i, hadNewLine);
		i++;
    }
}

void saveData(char *filePath){
	uint32_t i = 0;
	lineData *tmp = textBuffer.lines;

	FILE *wow = fopen(filePath, "w+");
    while (i < data.maxHeight) {
		if (i < textBuffer.usedRows){
			fprintf(wow, "%s", tmp->line);
			tmp = tmp->next;
		}
		else
	        printw("~\n");
        i++;
    }
}