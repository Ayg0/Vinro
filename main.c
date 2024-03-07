#include "vinro.h"
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint8_t		_CLOSE_WINDOW = 0; 	// toClose the ncurses Loop
uint8_t		_DONT_IGNORE = 0; 	// flag to not ignore the last word when init the line
vinroData	data;
buffer		textBuffer;
FILE		*file;
lineData	*currentLine = NULL;

void initTextBuffer(){
	textBuffer.nbRows = 0;
	textBuffer.startRowIndex = 0;
	textBuffer.lines = NULL;
	textBuffer.end = NULL;
}

void initVinro(){
    initscr();
	initTextBuffer();
    raw();
	noecho();
	cbreak();
    keypad(stdscr, TRUE);
	data.cursorPos.y = 0;
	data.cursorPos.x = 0;
	data.mode = CONTROL_MODE;
	data.attr.tabSize = 2;
	data.attr.fileOptions = 0;
    getmaxyx(stdscr, data.maxHeight, data.maxWidth);
	data.maxHeight--;
	data.infoBuffer = calloc(data.maxWidth, sizeof(char));
	if (!data.infoBuffer)
		displayError("Allocation Faild");
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
	lineData *tmp = textBuffer.start;
	clear();
    while (i < data.maxHeight) {
		move(i, 0);
		if (i < textBuffer.nbRows){
			printw("%s", tmp->line);
			tmp = tmp->next;
		}
		else
	        printw("~");
        i++;
    }
	mvprintw(data.maxHeight, 0, "%s", data.infoBuffer);
	move(data.cursorPos.y, data.cursorPos.x);
    return 0;
}

char getInput(){
    int c = getch();

	if (c == ERR)
		return 0;
	switch (data.mode) {
		case CONTROL_MODE:
			handleControlInput(c);
			break ;
		case EDIT_MODE:
			handleEditInput(c);
			break ;
	}
    return 1;
}

int main(int ac, char **av){
	setenv("TERM","xterm-256color", 1);
	setenv("ESCDELAY", "1", 1);
	if (ac != 3)
		displayError("didn't specify fileName");
    initVinro();
	loadData(av[1]);
    while (!_CLOSE_WINDOW) {
        refresh();
		updateInfoBuffer();
        outputBuffer();
        while(!getInput());
    }
    destructVinro();
	saveData(av[2]);
	//printf("number of Rows:%d\n", textBuffer.nbRows);
	//printf("Used Rows:%d\n", textBuffer.usedRows);
	//lineData *tmp = textBuffer.lines;
	//while (tmp) {
	//	printf("%d, %d, %s", tmp->size, tmp->hadNewLine, tmp->line);
	//	tmp = tmp->next;
	//}
    return 0;
}