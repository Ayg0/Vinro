#include "vinro.h"
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint8_t		_CLOSE_WINDOW = 0; 	// toClose the ncurses Loop
uint8_t		_DONT_IGNORE = 0; 	// flag to not ignore the last word when init the line
vinroData	data;
buffer		textBuffer;
FILE		*file;

void initTextBuffer(){
	textBuffer.nbRows = 0;
	textBuffer.usedRows = 0;
	textBuffer.cursorPos.x = 0;
	textBuffer.cursorPos.y = 0;
	textBuffer.lines = NULL;
	textBuffer.end = NULL;
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
	lineData *tmp = textBuffer.lines;
    while (i < data.maxHeight) {
		if (i < textBuffer.usedRows){
			printw("%s%c", tmp->line, !tmp->hadNewLine * '\n');
			tmp = tmp->next;
		}
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
	setenv("TERM","xterm-256color", 1);
	if (ac != 3)
		displayError("didn't specify fileName");
    initVinro();
	loadData(av[1]);
    while (!_CLOSE_WINDOW) {
        refresh();
        outputBuffer();
        getInput();
    }
    destructVinro();
	saveData(av[2]);
	printf("number of Rows:%d\n", textBuffer.nbRows);
	printf("Used Rows:%d\n", textBuffer.usedRows);
    return 0;
}