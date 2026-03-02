#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	print_result(int *board, int n)
{
	int i;
	char str[12];
	int len;

	i = 0;
	while (i < n)
	{
		len = sprintf(str, "%d", board[i]);
		write (1, str , len);
		if (i < n -1)
			write (1, " ", 1);
		i++;
	}
	write (1, "\n", 1);
}

int	is_safe(int *board, int col, int row)
{
	int i = 0;
	while (i < col)
	{
		//abs will return the absolute value 
		//this will check if there is a queen on the same row in previous columns
		//the first condition will check the same row
		//the second condition will check the diagonal attack
		if (board[i] == row || abs(board[i] - row) == abs(i - col))
			return (0);
		i++;
	}
	return (1);
}
void	backtrack(int *board, int col, int n)
{
	int row;

	//when the number of column is the same as n, meaning it is the last column
	if (col == n)
	{
		print_result(board, n);
		return ;
	}

	row = 0;
	while (row < n)
	{
		if (is_safe(board, col, row))
		{
			board[col] = row;
			backtrack(board, col+1, n);
		}
		row++;
	}
}

int main(int argc, char **argv)
{
	//the rule of this game is that the number of queen and the row and column of the board would be the same
	int n; //to accept the number of queens 
	int *board; //this is the array of integer to store the queen
	
	//this is to check if the userinput is only the number of queen or not
	if (argc != 2)
	{
		fprintf(stderr, "Usage %s <n of queen>\n", argv[0]); //this will print the content in file instead of stdout console
		return (1);
	}

	//if there are two argument, we will convert the char to num for that
	n = atoi(argv[1]);
	//check if the number is 0 or less than that, if so, the board cannot be created;
	if (n <= 0)
		return (0);

	//the board is created according to the number of queen
	board = (int *)calloc(n, sizeof(int));

	//if the board is not created properly
	if (!board)
	{
		fprintf(stderr, "Memory allocation failed\n");
		return (1);
	}

	//if the board is created successfully, we will add the queen to each role with backtracking
	backtrack(board, 0, n);

	//do not forget to free the board
	free(board);
	return 0;
}
