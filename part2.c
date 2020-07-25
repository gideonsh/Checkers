
#pragma once
#include "header.h"

void initializeListCell(SingleSourceMovesListCell* cell, SingleSourceMovesTreeNode* node)
{
	cell->position->row = node->Pos->row;
	cell->position->col = node->Pos->col;
	cell->captures = node->total_captures_so_far;
	cell->next = NULL;
	return;
}

SingleSourceMovesTreeNode* getMaxValNode(SingleSourceMovesTreeNode* root)
// Find and return the node with most total_captures_so_far in the tree that "root" is the root
{
	if (root == NULL)
	{
		return NULL;
	}
	SingleSourceMovesTreeNode* res = root;
	SingleSourceMovesTreeNode* leftRes = getMaxValNode(root->next_move[0]);
	SingleSourceMovesTreeNode* rightRes = getMaxValNode(root->next_move[1]);
	if (leftRes != NULL && leftRes->total_captures_so_far >= res->total_captures_so_far)
	{
		res = leftRes;
	}
	if (rightRes != NULL && rightRes->total_captures_so_far >= res->total_captures_so_far)
	{
		res = rightRes;
	}
	return res;
}

SingleSourceMovesList* createEmptyList()
{
	SingleSourceMovesList* lst = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	checkMemoryAlloc(lst, lst);
	lst->head = NULL;
	lst->tail = NULL;
	return lst;
}
void appendNodeToList(SingleSourceMovesList* lst, SingleSourceMovesTreeNode* node)
// Creates a SingleSourceMovesListCell from a given SingleSourceMovesTreeNode and append it to the begining (head)
// of the list lst.
{
	if (node == NULL)
	{
		return;
	}
	SingleSourceMovesListCell* cell = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell));
	checkMemoryAlloc(cell, cell);
	cell->position = (checkersPos*)malloc(sizeof(checkersPos));
	checkMemoryAlloc(cell->position, cell->position);
	initializeListCell(cell, node);
	/* insert lstCell to head of List */
	if (lst->head == NULL && lst->tail == NULL)
	{
		lst->head = cell;
		lst->tail = cell;
		return;
	}
	cell->next = lst->head;
	lst->head = cell;
}

int addNodesToList(SingleSourceMovesTreeNode* root, SingleSourceMovesTreeNode* target,
	SingleSourceMovesList* lst)
	/* Given a SingleSourceMovesTree with "root" as its root, creates a path to the target node "target"
	* and inserts that path to lst.
	*/
{
	if (root == NULL)
	{
		return 0;
	}
	if (root == target ||
		addNodesToList(root->next_move[0], target, lst) ||
		addNodesToList(root->next_move[1], target, lst))
	{
		appendNodeToList(lst, root);
		return 1;
	}
	return 0;
}
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree)
{
	/* gets a source and returns the path with the most captures */
	//unsigned short saveCaptures = moves_tree->source->total_captures_so_far;
	SingleSourceMovesTreeNode* srcMove = moves_tree->source;
	if (srcMove == NULL)
	{
		return NULL;
	}
	//srcMove->total_captures_so_far = -1;
	SingleSourceMovesTreeNode* target = getMaxValNode(srcMove); // Node with the highest captures_so_far
	SingleSourceMovesList* lst = createEmptyList();
	addNodesToList(srcMove, target, lst);
	return lst;
}

