#pragma once
#include "header.h"

void   insertNodeToList(MultipileSourceMovesList* multiLst, MultipleSourceMovesListCell* multiCell)
{
	MultipleSourceMovesListCell* curr, *save;
	multiCell->next = NULL;
	if (multiLst->head == NULL)
	{
		multiLst->head = multiCell;
		multiLst->tail = multiCell;
	}
	// insert to tail //
	else
	{
		save = multiCell;
		multiLst->tail->next = save;
		multiLst->tail = save;
	}
}
MultipleSourceMovesListCell* allocateMultiCell(SingleSourceMovesList* moveList)
{
	MultipleSourceMovesListCell* multiCell = (MultipleSourceMovesListCell*)malloc(sizeof(MultipleSourceMovesListCell));
	checkMemoryAlloc(multiCell, multiCell);
	multiCell->single_source_moves_list = moveList;
	multiCell->next = NULL;
	return multiCell;
}
MultipileSourceMovesList*   createEmptyMultiListMove()
{
	MultipileSourceMovesList* multMoveList = (MultipileSourceMovesList*)malloc(sizeof(MultipileSourceMovesList));
	checkMemoryAlloc(multMoveList, multMoveList);
	multMoveList->head = NULL;
	multMoveList->tail = NULL;
	return multMoveList;
}
checkersPos* allocateChecker(int row, int col)
{
	checkersPos* checker = (checkersPos*)malloc(sizeof(checkersPos));
	checkMemoryAlloc(checker, checker);
	checker->row = rowToChar(row);
	checker->col = colToChar(col);
	return checker;
}
void findCheckersOnBoard(Player player, Board board, MultipileSourceMovesList* PlayerListMove)
{        // this function finds chekers on board and creates a list of moves for all the player chekcers//
	int     i, j;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == player)
			{        // found a player checker on the board//
				checkersPos* checker = allocateChecker(i, j);
				//create a move tree for the cheker that we found on the board//
				SingleSourceMovesTree* singleMoveTr = FindSingleSourceMoves(board, checker);
				// now we wil find the optimal move path for cheker//
				SingleSourceMovesList*  moveList = createEmptyList();
				moveList = FindSingleSourceOptimalMove(singleMoveTr);//seif 2
				MultipleSourceMovesListCell* multiCell = allocateMultiCell(moveList);
				//insert the multisourcemovelistcell to multisourcemovelist
				insertNodeToList(PlayerListMove, multiCell);
			}
		}
	}
}

MultipileSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player)
{
	/* need to find all the "players"  type that can move */
	MultipileSourceMovesList* pPlayerListMove = createEmptyMultiListMove();
	checkMemoryAlloc(pPlayerListMove, pPlayerListMove);
	// need to find all the 'T' or all the 'B' in the board //
	if (player == 'T')
	{
		findCheckersOnBoard(player, board, pPlayerListMove);
	}
	else
	{
		findCheckersOnBoard(player, board, pPlayerListMove);
	}
	return pPlayerListMove;
}
