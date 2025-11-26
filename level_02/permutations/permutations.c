#include <stdio.h>

void	ft_swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void ft_sort(char *s)
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
		return ;
	}
	ft_sort(s + l);
	for(int i = l; i <= r; i++)
	{
		ft_swap(&s[l], &s[i]);
		perm(s, l + 1, r);
		ft_swap(&s[l], &s[i]);
	}
}