#include "vinro.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t mystrlen(char *line, uint8_t *hadNewLine){
	uint32_t i = 0;

	while (line[i]) {
		if (line[i] == '\r' || line[i] == '\n'){
			line[i] = 0;
			*hadNewLine = 1;
		}
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

	line[0] = '\0';
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
	if (textBuffer.lines == NULL)
		appendRow(line, 1, 0, 0);
	currentLine = textBuffer.lines;
}

void saveData(char *filePath){
	lineData *tmp = textBuffer.lines;

	FILE *wow = fopen(filePath, "w+");
    while (tmp) {
		fprintf(wow, "%s", tmp->line);
		if (tmp->hadNewLine)
			fprintf(wow, "\n");
		tmp = tmp->next;
    }
	fclose(wow);
}