#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 

// função para printar board[i] e enquanto nao for a ultima ou seja n - 1 ele coloca espaço.
// ao final de tudo do um \n e pronto GG go next ez pz leamon squezy
void	print_board(int *board, int n)
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
// aqui é só pra ver se a board[i] é valida
// ou seja se ela tiver na mesma coluna ou na diagonal elas podem se comer, se não é sucesso.
// verificar sempre se o buffer[i] é igual a col
// depois se buffer[i] - 1 é igual a col - row
// por fim se buffer[i] + 1 é igual a col + row
// qualquer situação dessa já era não é valido, elas podem se comer

int	is_valid(int *board, int row, int col)
{
	int i = 0;
	while(i < row)
	{
		if(board[i] == col)
			return 0;
		if((board[i] - i) == (col - row))
			return 0;
		if((board[i] + i) == (col + row))
			return 0;
		i++;
	}
	return 1;
}


// aqui sempre que o board for valido ele na posicao row vai receber o col e vai chamar a recursividade
// a recursiva vai ser o row na proxima posicao ou seja proxima linha. iteramos o col pra ir pra proxima tambem mas fora do loop
void	nqueen(int n, int *board, int row)
{
	int col = 0;
	if(row == n)
	{
		print_board(board, n);
		return;
	}
	while(col < n)
	{
		if(is_valid(board, row, col))
		{
			board[row] = col;
			nqueen(n, board, row + 1);
		}
		col++;
	}
}

// aqui pegamos o nosso argumentos e colocamos dentro de n usando atoi
// inicializamos o nosso board com 10000 pra dar handle nos testes que algum sapeca fizer
// inicializamos todas as posicoes do board a 0 pq falando de inteiros pode ter garbage dentro das posicoes
// chamamos a recursiva basicona, passando o nosso argumento o board e 0 que será a linha inicial.
int main(int ac, char **av)
{
	if(ac != 2 || !av[1][0])
		return 1;
	int n = atoi(av[1]);
	int i = 0;
	int board[10000];
	while(i < n)
		board[i++] = 0;
	nqueen(n, board, 0);
	return(0);
}