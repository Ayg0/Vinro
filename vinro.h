#ifndef VINRO_H
# define VINRO_H

#include <curses.h>
#include <ncurses.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>


enum MODS{
	EDIT_MODE,
	CONTROL_MODE,
};

typedef struct _position{
	uint32_t x;
	uint32_t y;
} position;

typedef struct _attributes{
	uint8_t	tabSize;
} attributes;


typedef struct _vinroData{
    uint32_t	maxWidth;
    uint32_t	maxHeight;
	attributes	attr;
    uint8_t		mode;
	position	cursorPos;
	char 		*infoBuffer;
} vinroData;


typedef struct _line{
	uint32_t		size;
	uint8_t			hadNewLine;
	char			*line;
	struct _line	*prev;
	struct _line	*next;
} lineData;

typedef struct _buffer {
    lineData	*lines;
	uint32_t	usedRows;
	uint32_t	nbRows;
	lineData	*end;
} buffer;

#define KEY_ESC 27

void 	displayError(char *err);
uint8_t appendRow(char *line, uint32_t lineSize, uint32_t atRow, uint8_t hadNewLine);
void 	loadData(char *fileName);
void 	saveData(char *filePath);

lineData *getRow(uint32_t index);

// line Manipulation:
void	insertCharacter(lineData *thisLine, char c, int32_t x, int32_t y);
void	deleteCharacter();
void	enter();
// cursor Manipulation:
void moveCursor(int32_t x, int32_t y);
// string Manipulation:
void splitString(lineData *line, lineData *next, int32_t index);
// input Helper:
void 	updateInfoBuffer();
void	handleEditInput(int c);
void	handleControlInput(int c);

extern FILE			*file;
extern vinroData	data;
extern buffer 		textBuffer;
extern uint8_t 		_DONT_IGNORE;
extern uint8_t		_CLOSE_WINDOW;
extern lineData		*currentLine;
#endif