#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void	printboard(int *board, int n)
{
	int i = 0;
	while(i < n)
	{
		fprintf(stdout, "%d", board[i]);
		if(i < n - 1)
			fprintf(stdout, " ");
		i++;
	}
	fprintf(stdout, "\n");
}

int	board_is_valid(int *board, int row, int col)
{
	int i = 0;
	while(i < row)
	{
		if(board[i] == col)
			return 0;
		if((board[i] + i) == (col + row))
			return 0;
		if((board[i] - i) == (col - row))
			return 0;
		i++;
	}
	return (1);
}

void	nqueens(int n, int *board, int row)
{
	int col = 0;
	if(row == n)
	{
		printboard(board, n);
		return;
	}
	while(col < n)
	{
		if(board_is_valid(board, row, col))
		{
			board[row] = col;
			nqueens(n, board, row + 1);
		}
		col++;
	}
}

int main(int ac, char **av)
{
	if(ac != 2 || !av[1][0])
		return 1;
	
	int board[10000];
	int n = atoi(av[1]);
	int i = 0;
	while(i < n)
		board[i++] = 0;
	nqueens(n, board, 0);
}