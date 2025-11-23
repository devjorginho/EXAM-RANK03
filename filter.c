#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 100000

int	ft_strncmp(char *s1, char *s2, int n)
{
	int i = 0;
	while(i < n && (s1[i] || s2[i]))
	{
		if(s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{
	if(ac != 2 || av[1][0] == '\0')
		return (1);
	char buffer[BUFFER_SIZE];
	char *pattern = av[1];
	int	pattern_len = strlen(av[1]);
	int i = 0;
	int j;	
	char c;
	int bytes_read = read(0, &c, 1);

	if(bytes_read == -1)
	{
		fprintf(stderr, "Error: ");
		perror(NULL);
		return (1);
	}
	while(bytes_read > 0)
	{
		buffer[i] = c;
		bytes_read = read(0, &c, 1);
		if(bytes_read == -1)
		{
			fprintf(stderr, "Error: ");
			perror(NULL);
			return (1);
		}	
		i++;
	}
	buffer[i] = '\0';
	i = 0;
	while(buffer[i])
	{
		j = 0;
		if(!(ft_strncmp(pattern, &buffer[i], pattern_len)))
		{
			while(j++ < pattern_len)
				write(1, "*", 1);
			i += pattern_len;
		}
		else
		{
			write(1, &buffer[i], 1);
			i++;
		}
	}
	return (0);
}
