#pragma once
#include "header.h";
void convertFromBoard(Board  board, unsigned short int* buffer, int i, int j)
{
	if (board[i][j] == 'T')
	{
		*buffer = *buffer << 2;
		*buffer = *buffer | 1;
	}
	else if (board[i][j] == ' ')
		*buffer = *buffer << 2;
	else
	{
		*buffer = *buffer << 2;
		*buffer = *buffer | 2;
	}
}

void StoreBoard(Board board, char* filename)
{
	FILE* file = fopen(filename, "wb");
	int i, j;
	unsigned short int buffer = 0, slot, emptyRow = 0;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			convertFromBoard(board, &buffer, i, j);
		}
		fwrite(&buffer, sizeof(unsigned short int), 1, file);
	}
	fclose(file);
}
