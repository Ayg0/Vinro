#include "vinro.h"
#include <ncurses.h>
#include <stdint.h>

unsigned char _CLOSE_WINDOW = 0;
vinroData	data;
buffer		textBuffer;


void loadData(){
	textBuffer.nbRows = 0;
	textBuffer.usedRows = 0;
	textBuffer.cursorPos.x = 0;
	textBuffer.cursorPos.y = 0;
	textBuffer.lines = NULL;
	appendRow("Hello World", 12, 0);
	appendRow("Hello guys!", 12, 1);
	appendRow("Hello guys!", 12, 2);
}

void initVinro(){
    initscr();
    raw();
    keypad(stdscr, TRUE);
	noecho();
	loadData();
    getmaxyx(stdscr, data.maxHeight, data.maxWidth);
}

void destructVinro(){
    endwin();
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
			printw("%s\n", textBuffer.lines[i].line);
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

int main(){
    initVinro();
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