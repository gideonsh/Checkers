#include "Header.h"


void printBoard(Board board)
{
	char c;
	int counter = 1, row = 0, col = 0;
	for (int i = 0; i < 19; i++)
	{
		if (i % 2 == 0)
			printf("+-+-+-+-+-+-+-+-+-+");
		for (int j = 0; j < 19; j++)
		{
			if (i == 1 && j == 0)
				printf("+");
			else if (i == 1 && j == 1)
				printf(" ");
			else if (i % 2 != 0) // i is odd
			{
				if (i == 1 && j == 0)
					printf("+ ");
				else if (j % 2 == 0)
					printf("|");
				else if ((i == 1) && (j > 2) && (j % 2 == 1))
					printf("%d", counter++);
				else if (j == 1 && i > 2)
				{
					c = (char)(64 + i / 2);
					printf("%C", c);
				}
				else if (j % 2 != 0)
				{
					row = (i - 1) / 2 - 1;
					col = (j - 1) / 2 - 1;
					printf("%c", board[row][col]);
				}
			}
		}
		printf("\n");
	}
}
//TODO - maybe this is useful maybe not...
void initBoard(Board* b) {
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			(*b)[i][j] = ' ';
		}
	}
}

int main()
{
	SingleSourceMovesTree *source;
	Board board;
	checkersPos src;
	src.row = 'A';
	src.col = '4';
	initBoard(&board);
	board[0][0] = ' '; board[0][1] = 'T'; board[0][2] = ' '; board[0][3] = 'T'; board[0][4] = ' '; board[0][5] = 'T'; board[0][6] = ' '; board[0][7] = 'T';

	board[1][0] = 'T'; board[1][1] = ' '; board[1][2] = 'T'; board[1][3] = ' '; board[1][4] = 'B'; board[1][5] = ' '; board[1][6] = 'T'; board[1][7] = ' ';

	board[2][0] = ' '; board[2][1] = 'T'; board[2][2] = ' '; board[2][3] = ' '; board[2][4] = ' '; board[2][5] = 'T'; board[2][6] = ' '; board[2][7] = 'T';

	board[3][0] = 'B'; board[3][1] = ' '; board[3][2] = 'B'; board[3][3] = ' '; board[3][4] = 'B'; board[3][5] = ' '; board[3][6] = 'B'; board[3][7] = ' ';

	board[4][0] = ' '; board[4][1] = ' '; board[4][2] = ' '; board[4][3] = ' '; board[4][4] = ' '; board[4][5] = 'B'; board[4][6] = ' '; board[4][7] = 'B';

	board[5][0] = 'B'; board[5][1] = ' '; board[5][2] = 'B'; board[5][3] = ' '; board[5][4] = 'B'; board[5][5] = ' '; board[5][6] = 'B'; board[5][7] = ' ';

	board[6][0] = ' '; board[6][1] = ' '; board[6][2] = ' '; board[6][3] = ' '; board[6][4] = ' '; board[6][5] = 'B'; board[6][6] = ' '; board[6][7] = 'B';

	board[7][0] = 'B'; board[7][1] = ' '; board[7][2] = 'B'; board[7][3] = ' '; board[7][4] = 'B'; board[7][5] = ' '; board[7][6] = 'B'; board[7][7] = ' ';









	printBoard(board);
	printf("\n");
	printf("\n");

	/*source = FindSingleSourceMoves(board, &src);
	 printTreeInorder(*source);
	 SingleSourceMovesList* lst = FindSingleSourceOptimalMove(source); /* part 2*/
	/* MultipileSourceMovesList* allPlayersList = FindAllPossiblePlayerMoves(board, 'T'); /* part 3*/
	 //turn(board, 'B'); 
	 char str[13] = "MaxAndGideon";
	 StoreBoard(board, str); 
	 initBoard(&board);
	 printBoard(board);
	 LoadBoard(str, board);
	//PlayGame(board, 'T');
	printBoard(board);
	printf("\n");
	printf("\n");
	system("pause");
	return 0;
}