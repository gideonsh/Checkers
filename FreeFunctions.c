
#include "header.h"

void freeNodeFromTree(SingleSourceMovesTreeNode* root)
{
	free(root->Pos);
	root->Pos = NULL;
	free(root);
	root = NULL;
	return;
}

void freeTreeMoves(SingleSourceMovesTreeNode* root)
{
	if (root->next_move[0] == NULL && root->next_move[1] == NULL)
	{
		freeNodeFromTree(root);
		root = NULL;
		return;
	}
	if (root->next_move[0])
	{
		freeTreeMoves(root->next_move[0]);
		root->next_move[0] = NULL;
	}
	if (root->next_move[1])
	{
		freeTreeMoves(root->next_move[1]);
		root->next_move[1] = NULL;
	}
	freeNodeFromTree(root);
	root = NULL;
}

void freeMultipileSourceMovesList(MultipileSourceMovesList* list)
{
	MultipleSourceMovesListCell* currMulti = list->head;
	MultipleSourceMovesListCell* nextMulti;
	SingleSourceMovesListCell* currSingle;
	SingleSourceMovesListCell* nextSingle;
	while (currMulti != NULL)
	{
		currSingle = currMulti->single_source_moves_list->head;
		while (currSingle != NULL)
		{
			free(currSingle->position);
			nextSingle = currSingle->next;
			free(currSingle);
			currSingle = nextSingle;
		}
		nextMulti = currMulti->next;
		free(currMulti->single_source_moves_list);
		free(currMulti);
		currMulti = nextMulti;
	}
	free(list);
}