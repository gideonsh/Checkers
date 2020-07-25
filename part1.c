
#pragma once
#include "Header.h"
#define PLAYER_MOVE(player) ((player=='T') ? (1) : (-1))
#define ENEMY(player) ((player == 'T') ? ('B') : ('T'))
#define SIDE(side) ((side == "left") ? (-1) : (1))
#define LAST_ROW(player) ((player == 'T') ? ('H') : ('A'))///// (7) : (0)
#define charToRow(row) ((row - 'A'))
#define charToCol(col) ((col - '1'))
int charToRowFunc(char row)
{
	return row - 'A';
}
int charToColFunc(char col)
{
	return col - '1';
}
char rowToChar(int row)
{
	return row + 'A';
}
char colToChar(int col)
{
	return col + 1 + '0';
}

SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src)
{
	Player player;
	SingleSourceMovesTree *tr;
	int step_taken = 0;
	player = board[charToRow(src->row)][charToCol(src->col)];
	if (player == ' ')  // TODO make sure player is NULL when empty position on board.
	{
		return NULL;
	}
	else
	{
		tr = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
		checkMemoryAlloc(tr, tr);
		tr->source = SingleSourceMovesTreeAux(board, src, player, 0, &step_taken);
		return tr;
	}
}

void createNode(SingleSourceMovesTreeNode** node, Board board, checkersPos *src, unsigned short total_captures_so_far)
{
	(*node) = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	checkMemoryAlloc((*node), (*node));
	(*node)->Pos = (checkersPos*)malloc(sizeof(checkersPos));
	checkMemoryAlloc((*node)->Pos, (*node)->Pos);
	copyBoard(board, ((*node)->board)); //(*node)->board = board;
	(*node)->Pos->row = src->row;
	(*node)->Pos->col = src->col;
	(*node)->total_captures_so_far = total_captures_so_far;
	(*node)->next_move[0] = (*node)->next_move[1] = NULL;
}

SingleSourceMovesTreeNode* SingleSourceMovesTreeAux(Board board, checkersPos *src, Player player, unsigned short captures, int *step_taken)
{
	SingleSourceMovesTreeNode *node;
	checkersPos  dest_left, dest_right;
	dest_left.row = dest_left.col = ' ';
	dest_right.row = dest_right.col = ' ';
	unsigned short capsLeft = captures;
	unsigned short capsRight = captures;
	playerIsAbleToMove(board, src, player, &capsLeft, &capsRight, &dest_left, &dest_right, step_taken);
	//playerIsAbleToMove(board, src, player, &captures, &dest_left, &dest_right, step_taken);
	createNode(&node, board, src, captures);
	if (dest_left.row == ' ' && dest_right.row == ' ')
		return node;
	else if (dest_left.row != ' ' && dest_right.row != ' ')
	{
		(*step_taken)++;
		node->next_move[0] = SingleSourceMovesTreeAux(board, &dest_left, player, capsLeft, step_taken);
		node->next_move[1] = SingleSourceMovesTreeAux(board, &dest_right, player, capsRight, step_taken);
	}
	else if (dest_right.row == ' ')
	{
		(*step_taken)++;
		node->next_move[0] = SingleSourceMovesTreeAux(board, &dest_left, player, capsLeft, step_taken);
	}
	else
	{
		(*step_taken)++;
		node->next_move[1] = SingleSourceMovesTreeAux(board, &dest_right, player, capsRight, step_taken);
	}
	return node;
}

void playerIsAbleToMove(Board board, checkersPos *src, Player player, unsigned short *cLeft, unsigned short *cRight,
	checkersPos  *dest_left, checkersPos *dest_right, int *step_taken)
{
	char left, right;
	int res = 0;
	if (!isFinishLine(src, player));//0 - player is not at the last row 1 - player is at the last row
	{
		nextToWall(src, &left, &right); //0 - not blocked, 1 - blocked from left, 2 - blocked from right.
		blockedByPlayer(board, src, player, &left, &right, dest_left, dest_right, step_taken);
		if (left == ENEMY(player) && right == ENEMY(player))
		{
			canCapture(board, src, &left, &right, dest_left, dest_right, player, cLeft, step_taken);
			canCapture(board, src, &left, &right, dest_left, dest_right, player, cRight, step_taken);
			return;
		}
		else if (right == ENEMY(player))
			canCapture(board, src, &left, &right, dest_left, dest_right, player, cRight, step_taken);
		else if (left == ENEMY(player))
			canCapture(board, src, &left, &right, dest_left, dest_right, player, cLeft, step_taken);
		else if ((*step_taken) > 0)
		{
			dest_left->row = ' ';
			dest_left->col = ' ';
			dest_right->row = ' ';
			dest_right->col = ' ';
		}
	}
	return;
}

void canCapture(Board board, checkersPos *src, char *left, char *right, checkersPos *dest_left, checkersPos *dest_right, Player player, unsigned short *captures, int *step_taken)
{
	if ((*captures) > 0)
		((*step_taken) = 0);
	if (src->row + PLAYER_MOVE(player) == LAST_ROW(player))
		return;

	else
	{
		if (*left != player && *left != ' ' && (*step_taken) == 0)
			captureChecks(board, src, player, "left", dest_left, captures);
		else if (*step_taken > 0)
		{
			dest_left->row = ' ';
			dest_left->col = ' ';
		}
		if (*right != player && *right != ' ' && (*step_taken) == 0)
			captureChecks(board, src, player, "right", dest_right, captures);
		else if (*step_taken > 0)
		{
			dest_right->row = ' ';
			dest_right->col = ' ';
		}
		return;
	}
}

void captureChecks(Board board, checkersPos *src, Player player, char *side, checkersPos *dest_side, unsigned short *captures)
{
	if ((charToCol(src->col) + (SIDE(side) * 2) >= 0) && (charToCol(src->col)) + (SIDE(side) * 2) < 8)//22.7.19 change to < 8 from < 9
	{
		if (board[charToRow(src->row) + (PLAYER_MOVE(player) * 2)][charToCol(src->col) + (SIDE(side) * 2)] == ' ')
		{
			dest_side->row = src->row + (PLAYER_MOVE(player) * 2);
			dest_side->col = src->col + (SIDE(side) * 2);
			(*captures)++;
		}
	}
	return;
}

void blockedByPlayer(Board board, checkersPos *src, Player player, char *left, char *right, checkersPos *dest_left,
	checkersPos *dest_right, int* step_taken)
{
	if (*left == 'w')
		*right = destinationsChecks(board, src, player, "right", dest_right, step_taken);
	else if (*right == 'w')
		*left = destinationsChecks(board, src, player, "left", dest_left, step_taken);
	else
	{
		*left = destinationsChecks(board, src, player, "left", dest_left, step_taken);
		*right = destinationsChecks(board, src, player, "right", dest_right, step_taken);
	}
}

char destinationsChecks(Board board, checkersPos *src, Player player, char *side, checkersPos *dest_side, int * step_taken) // DEBUG for side
{
	if (board[charToRow(src->row) + PLAYER_MOVE(player)][charToCol(src->col) + SIDE(side)] == player)
		return player;
	else if (board[charToRow(src->row) + PLAYER_MOVE(player)][charToCol(src->col) + SIDE(side)] == ENEMY(player))
		return ENEMY(player);
	else//revach
	{
		if (*step_taken == 0)
		{
			dest_side->row = src->row + PLAYER_MOVE(player);
			dest_side->col = src->col + SIDE(side);
		}
		return ' ';
	}
}


void nextToWall(checkersPos *src, char *left, char *right)
{
	if (src->col == '1')
		*left = 'w';
	else if (src->col == '8')
		*right = 'w';
	return;
}

int isFinishLine(checkersPos *src, Player player)
{
	if (player == 'T')
	{
		if (src->row == 'H')

			return 1;
		return 0;
	}
	else
		//if (player == 'B')
	{
		if (src->row == 'A')
			return 1;
		return 0;
	}
}

void checkMemoryAlloc(void *wanted_alloc, void *mem_control) {  // void * to match all pointers - general allocation test func.
	if (wanted_alloc == NULL) {
		free(mem_control);
		printf("memory didn't allocate...Exiting program.");
		exit(1);
	}
}

void copyBoard(Board board, Board new_board)
{     // update the board //
	int i, j;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			(new_board)[i][j] = (board)[i][j];
		}
	}
}
void printTreeInorder(SingleSourceMovesTree head)
{
	printTreeInorderAux(head.source);
	printf("\n");
}
void printTreeInorderAux(SingleSourceMovesTreeNode *node)
{
	if (node)
	{
		printTreeInorderAux(node->next_move[0]);
		printf("%c %c\n", node->Pos->row, node->Pos->col);
		printTreeInorderAux(node->next_move[1]);
	}
}