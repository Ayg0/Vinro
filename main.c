#include "vinro.h"
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

unsigned char _CLOSE_WINDOW = 0;
vinroData	data;
buffer		textBuffer;
FILE		*file;


void loadData(char *fileName){
	char line[data.maxWidth];

	file = fopen(fileName, "a+");
	if (!file)
		displayError("File \?\?!");
	//appendRow("Hello World", 12, 0);
	//appendRow("Hello guys!", 12, 1);
	//appendRow("Hello guys!", 12, 2);
	rewind(file);
	int i = 0;
	while (fgets(line, sizeof(line), file) != NULL) {
        appendRow(line, strlen(line), i);
		i++;
    }
}

void initTextBuffer(){
	textBuffer.nbRows = 0;
	textBuffer.usedRows = 0;
	textBuffer.cursorPos.x = 0;
	textBuffer.cursorPos.y = 0;
	textBuffer.lines = NULL;
}

void initVinro(){
    initscr();
	initTextBuffer();
    raw();
    keypad(stdscr, TRUE);
	noecho();
    getmaxyx(stdscr, data.maxHeight, data.maxWidth);
}

void destructVinro(){
    endwin();
	fclose(file);
}

void displayError(char *err){
	destructVinro();
	printf("Err, %s !!\n", err);
	exit(1);
}

char outputBuffer(){
    uint32_t i = 0;
    while (i < data.maxHeight) {
		if (i < textBuffer.usedRows)
			printw("%s", textBuffer.lines[i].line);
		else
	        printw("~\n");
        i++;
    }
    return 0;
}

char getInput(){
    int c = getch();
    if (c == 'q')
        _CLOSE_WINDOW = 1;
    return 0;
}

int main(int ac, char **av){
	if (ac != 2)
		displayError("didn't specify fileName");
    initVinro();
	loadData(av[1]);
    while (!_CLOSE_WINDOW) {
        refresh();
        outputBuffer();
        getInput();
    }
    destructVinro();
	printf("number of Rows:%d\n", textBuffer.nbRows);
	printf("Used Rows:%d\n", textBuffer.usedRows);
    return 0;
}