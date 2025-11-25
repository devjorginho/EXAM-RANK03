#include <stdio.h>

int	min_to_remove(char *s)
{
	int open = 0;
	int close = 0;
	int i = 0;
	
	while(s[i])
	{
		if(s[i] == '(')
			open++;
		if(s[i] == ')')
		{
			if(open > 0)
				open--;
			else
				close++;
		}
		i++;
	}
	return (open + close);
}

void	solve(int index, int to_remove, int removed, char *s)
{
	if(removed > to_remove)
		return;
	if(s[index] == '\0')
	{
		if(to_remove == removed && min_to_remove(s) == 0)
			puts(s);
		return;
	}
	if(s[index] == ')' || s[index] == '(')
	{
		char temp = s[index];
		s[index] = ' ';
		solve(index + 1, to_remove, removed + 1, s);
		s[index] = temp;
	}
	solve(index + 1, to_remove, removed, s);
}
int main(int ac, char **av)
{
	if(ac != 2)
		return 1;
	if(min_to_remove(av[1]) == 0)
	{
		puts(av[1]);
		return 0;
	}
	solve(0, min_to_remove(av[1]), 0, av[1]);
	return 0;
}