
#pragma once
#include "header.h"
#define BYTE_SIZE 8
void LoadBoard(char *filename, Board board)
{
	FILE *f = fopen(filename, "rb");
	int i, j;
	unsigned short int buffer = 0x0000;
	unsigned short int mask = 0xc000;
	unsigned short int row = 0x0000;
	for (i = 0; i < BYTE_SIZE; i++)
	{
		fread(&buffer, sizeof(unsigned short int), 1, f);
		for (j = 0; j < BYTE_SIZE; j++)
		{
			row = mask & buffer;
			row = row >> 14;
			addToBoard(board, row, i, j);
			buffer = buffer << 2;
		}
	}
	fclose(f);
}

void addToBoard(Board board, unsigned short int row, int i, int j)
{
	if (row == 0)
		board[i][j] = ' ';
	else if (row == 1)
		board[i][j] = 'T';
	else if (row == 2)
		board[i][j] = 'B';
}
