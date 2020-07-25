#pragma once

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string.h>
#define BOARD_SIZE 8
#define TRUE 1
#define FALSE 0
typedef struct _checkersPos
{
	char row, col;
}checkersPos;
typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];
typedef char Player;

typedef struct _SingleSourceMovesListCell
{
	checkersPos *position;
	unsigned short captures;
	struct _SingleSourceMovesCell *next;
}SingleSourceMovesListCell;

typedef struct _SingleSourceMovesList
{
	SingleSourceMovesListCell *head;
	SingleSourceMovesListCell *tail;
}SingleSourceMovesList;

typedef struct _MultipleSourceMovesListCell
{
	SingleSourceMovesList* single_source_moves_list;
	struct _MultipleSourceMovesListCell* next;
}MultipleSourceMovesListCell;

typedef struct _multipileSourceMovesList
{
	MultipleSourceMovesListCell* head;
	MultipleSourceMovesListCell* tail;
}MultipileSourceMovesList;


typedef struct _SingleSourceMovesTreeNode
{
	Board board;
	checkersPos *Pos;
	unsigned short total_captures_so_far;
	struct _SingleSourceMovesTreeNode *next_move[2];
}SingleSourceMovesTreeNode;

typedef struct _SingleSourceMovesTree
{
	SingleSourceMovesTreeNode *source;
}SingleSourceMovesTree;

SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src);
void createNode(SingleSourceMovesTreeNode** node, Board board, checkersPos *src, unsigned short total_captures_so_far);
SingleSourceMovesTreeNode* SingleSourceMovesTreeAux(Board board, checkersPos *src, Player player, unsigned short captures, int *steps_taken);
void playerIsAbleToMove(Board board, checkersPos *src, Player player, unsigned short *cLeft, unsigned short *cRight,
	checkersPos  *dest_left, checkersPos *dest_right, int *step_taken);
void canCapture(Board board, checkersPos *src, char *left, char *right, checkersPos *dest_left, checkersPos *dest_right, Player player, unsigned short *captures, int *steps_taken);
void captureChecks(Board board, checkersPos *src, Player player, char *side, checkersPos *dest_side, unsigned short *captures);
void blockedByPlayer(Board board, checkersPos *src, Player player, char *left, char *right, checkersPos *dest_left, checkersPos *dest_right);
char destinationsChecks(Board board, checkersPos *src, Player player, char *side, checkersPos *dest_side); // DEBUG for side
void nextToWall(checkersPos *src, char *left, char *right);
int isFinishLine(checkersPos *src, Player player);
void checkMemoryAlloc(void *wanted_alloc, void *mem_control);   // void * to match all pointers - general allocation test func.
void copyBoard(Board board, Board new_board);
void printTreeInorder(SingleSourceMovesTree head);
void printTreeInorderAux(SingleSourceMovesTreeNode *node);
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree);
int addNodesToList(SingleSourceMovesTreeNode* root, SingleSourceMovesTreeNode* target,
	SingleSourceMovesList* lst);
void appendNodeToList(SingleSourceMovesList* lst, SingleSourceMovesTreeNode* node);
SingleSourceMovesList* createEmptyList();
SingleSourceMovesTreeNode* getMaxValNode(SingleSourceMovesTreeNode* root);
void initializeListCell(SingleSourceMovesListCell* cell, SingleSourceMovesTreeNode* node);
MultipileSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player);
void   insertNodeToList(MultipileSourceMovesList* multiLst, MultipleSourceMovesListCell* multiCell);
MultipleSourceMovesListCell* allocateMultiCell(SingleSourceMovesList* moveList);
MultipileSourceMovesList*   createEmptyMultiListMove();
checkersPos* allocateChecker(int row, int col);
void findCheckersOnBoard(Player player, Board board, MultipileSourceMovesList* PlayerListMove);
void turn(Board board, Player player);
void betweenTwoPositions(SingleSourceMovesListCell* curr, SingleSourceMovesListCell* next, char *row, char *col);
int findMaxCaptures(SingleSourceMovesList* list);
void freeMultipileSourceMovesList(MultipileSourceMovesList* list);
void LoadBoard(char *filename, Board board);
void addToBoard(Board board, unsigned short int row, int i, int j);
void convertFromBoard(Board  board, unsigned short int* buffer, int i, int j);
void StoreBoard(Board board, char* filename);
void PlayGame(Board board, Player starting_player);
int EndGame(Board board, Player player);
int playerInTheFinishLine(Board board, Player player);
int AllEnemysCaptured(Board board, Player player);
void freeNodeFromTree(SingleSourceMovesTreeNode* root);
void freeTreeMoves(SingleSourceMovesTreeNode* root);
MultipleSourceMovesListCell* findCheckerThatCanMove(MultipleSourceMovesListCell* root);
void printMove(SingleSourceMovesList* playerMove);
void chooseTheBestMove(MultipleSourceMovesListCell* singlePlayer, int currCaptures, int nextCaptures, SingleSourceMovesList** bestMove);
void executeTheAction(Board board, Player player, SingleSourceMovesListCell* singleMove, SingleSourceMovesListCell* nextMove, char* row, char* col);