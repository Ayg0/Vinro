#ifndef VINRO_H
# define VINRO_H

#include <curses.h>
#include <ncurses.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>


enum ControlMods{
	EditMode,
	ControlMode,
};

typedef struct _vinroData{
    uint32_t	maxWidth;
    uint32_t	maxHeight;
    uint8_t		mode;
} vinroData;

typedef struct _position{
	uint32_t x;
	uint32_t y;
} position;

typedef struct _line{
	uint32_t	size;
	int8_t		*line;
} lineData;

typedef struct _buffer {
    lineData		*lines;
	uint32_t	usedRows;
	uint32_t	nbRows;
	position cursorPos;
} buffer;

void displayError(char *err);
uint8_t appendRow(char *line, uint32_t lineSize, uint32_t atRow);

#endif