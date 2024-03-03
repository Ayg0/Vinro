#include "vinro.h"
#include <stdint.h>
#include <string.h>

void	insertCharacter(int c){
	lineData *row = getRow(data.cursorPos.y);

	for (uint32_t i = row->size; i > data.cursorPos.x; i--)
		row->line[i] = row->line[i - 1];
	row->line[data.cursorPos.x] = c;
	data.cursorPos.x++;
	row->size++;
}

void deleteCharacter(){
	lineData *row = getRow(data.cursorPos.y);

	if (data.cursorPos.x == 0)
		return ;
	for (uint32_t i = data.cursorPos.x - 1; i < row->size; i++)
		row->line[i] = row->line[i + 1];
	row->line[row->size] = '\0'; 
	data.cursorPos.x--;
	row->size--;
}