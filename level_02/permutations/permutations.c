#include <stdio.h>

void	ft_swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_sort(char *s)
{
	int i = 0;
	int j;

	while(s[i])
	{
		j = 0;
		while(s[j + 1])
		{
			if(s[j] > s[j + 1])
				ft_swap(&s[j], &s[j + 1]);
			j++;
		}
		i++;
	}
}

void	perm(char *s, int l, int r)
{
	if(l == r)
	{
		puts(s);
		return;
	}
	ft_sort(s + l);
	for(int i = l; i <= r; i++)
	{
		ft_swap(&s[l], &s[i]);
		perm(s, l + 1, r);
		ft_swap(&s[l], &s[i]);
	}
}
int main(int ac, char **av)
{
	if(ac != 2 || !av[1][0])
		return 1;
	int n = 0;
	while(av[1][n])
		n++;
	perm(av[1], 0, n - 1);
	return 0;
}