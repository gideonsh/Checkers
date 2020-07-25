#pragma once
#include "header.h";
#define ENEMY(player) ((player == 'T') ? ('B') : ('T'))
#define LAST_ROW(player) ((player == 'T') ? ('H') : ('A'))

void PlayGame(Board board, Player starting_player)
{
	char prevPlayer, nextPlayer;
	nextPlayer = starting_player;
	prevPlayer = ENEMY(starting_player);
	while (!EndGame(board, prevPlayer))
	{
		if (nextPlayer == 'T')
			printf("player TOP_DOWNs turn\n");
		else if (nextPlayer == 'B')
			printf("player BOTTOM_UPs turn\n");
		turn(board, nextPlayer);
		printBoard(board);
		prevPlayer = nextPlayer;
		if (prevPlayer == 'T')
			nextPlayer = 'B';
		else
			nextPlayer = 'T';
	}
	printf("Player: %c Is The Winner Well Done It Was A Good Match! \n", prevPlayer);
}

int EndGame(Board board, Player player)
{
	if (playerInTheFinishLine(board, player) || AllEnemysCaptured(board, player))
		return 1;
	else
		return 0;
}



int playerInTheFinishLine(Board board, Player player)
{
	int i, j;
	char c;
	c = LAST_ROW(player);
	i = (int)(c - 65);
	for (j = 0; j < 8; j++)
	{
		if (board[i][j] == player)
			return 1;
	}
	return 0;
}

int AllEnemysCaptured(Board board, Player player)
{
	int i, j;
	char enemy = ENEMY(player);
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (board[i][j] == enemy)
				return 0;
		}
	}
	return 1;
}
