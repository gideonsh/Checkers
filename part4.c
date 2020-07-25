#pragma once
#include "header.h"
#define charToRow(row) ((row - 'A'))
#define charToCol(col) ((col - '1'))
#define ENEMY(player) ((player == 'T') ? ('B') : ('T'))



MultipleSourceMovesListCell* findCheckerThatCanMove(MultipleSourceMovesListCell* root)
{
	MultipleSourceMovesListCell* canMove = root;
	while (canMove)
	{
		if (canMove->single_source_moves_list->head != canMove->single_source_moves_list->tail)
			return 	canMove;
		canMove = canMove->next;
	}
	return canMove;
}

void turn(Board board, Player player)
{
	MultipileSourceMovesList* allPlayersList = FindAllPossiblePlayerMoves(board, player);/* part 3*/
	MultipleSourceMovesListCell* singlePlayer = allPlayersList->head;
	SingleSourceMovesList* bestMove = singlePlayer->single_source_moves_list;
	SingleSourceMovesListCell* singleMove, *nextMove;
	//singlePlayer = singlePlayer->next;
	int currCaptures, nextCaptures;
	char row, col;
	currCaptures = findMaxCaptures(bestMove);

	nextCaptures = currCaptures;
	chooseTheBestMove(singlePlayer, currCaptures, nextCaptures, &bestMove);

	if (currCaptures == 0 && bestMove->head == bestMove->tail)
	{// checker cannot capture and move , so find other checker that can move// 
		singlePlayer = findCheckerThatCanMove(allPlayersList->head);
		if (singlePlayer == NULL)
		{	
			printf("player %c cant move therefore player %c has won the game! \n", player, ENEMY(player));
			freeMultipileSourceMovesList(allPlayersList);
				exit(1);
		}
		bestMove = singlePlayer->single_source_moves_list;
	}
	singleMove = bestMove->head; 
	board[charToRow(bestMove->head->position->row)][charToCol(bestMove->head->position->col)] = ' ';
	nextMove = singleMove->next;
	executeTheAction(board, player, singleMove, nextMove, &row, &col);
	printMove(bestMove);
	freeMultipileSourceMovesList(allPlayersList);
}

void betweenTwoPositions(SingleSourceMovesListCell* curr, SingleSourceMovesListCell* next, char *row, char *col)//check what is the position of the enemy
{
	char colCurr, colNext, rowCurr, rowNext;
	rowCurr = curr->position->row;
	colCurr = curr->position->col;
	rowNext = next->position->row;
	colNext = next->position->col;
	if (rowCurr < rowNext)
		*row = rowCurr + 1;
	else
		*row = rowNext + 1;
	if (colCurr < colNext)
		*col = colCurr + 1;
	else
		*col = colNext + 1;
}

int findMaxCaptures(SingleSourceMovesList* list)
{
	SingleSourceMovesListCell *curr = list->head;
	int maxCapture = 0;
	while (curr != NULL)
	{
		maxCapture = curr->captures;
		curr = curr->next;
	}
	return maxCapture;
}

void printMove(SingleSourceMovesList* playerMove)
{
	SingleSourceMovesListCell* curr = playerMove->head;

	printf("%c%c", curr->position->row, curr->position->col);
	curr = curr->next;

	while (curr != NULL)
	{
		printf("->%c%c", curr->position->row, curr->position->col);
		curr = curr->next;
	}
	printf("\n");
}

void chooseTheBestMove(MultipleSourceMovesListCell* singlePlayer, int currCaptures, int nextCaptures, SingleSourceMovesList** bestMove)
{
	while (singlePlayer != NULL)// choose the path with the most capture
	{
		nextCaptures = findMaxCaptures(singlePlayer->single_source_moves_list);
		if (currCaptures < nextCaptures)
		{
			*bestMove = singlePlayer->single_source_moves_list;
			currCaptures = nextCaptures;
		}
		singlePlayer = singlePlayer->next;
	}
}

void executeTheAction(Board board, Player player, SingleSourceMovesListCell* singleMove, SingleSourceMovesListCell* nextMove, char* row, char* col)
{
	while (singleMove != NULL)//delete all the captured enemy's players and replace the player position with the best move
	{
		if (singleMove->next == NULL)
		{
			board[charToRow(singleMove->position->row)][charToCol(singleMove->position->col)] = player;
		}
		else
		{
			nextMove = singleMove->next;
			if (charToCol(singleMove->position->col) - charToCol(nextMove->position->col) == 2 || charToCol(singleMove->position->col) - charToCol(nextMove->position->col) == -2)
			{
				betweenTwoPositions(singleMove, nextMove, row, col);
				board[charToRow(*row)][charToCol(*col)] = ' ';
			}
		}
		singleMove = singleMove->next;
	}
}
