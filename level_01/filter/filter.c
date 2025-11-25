#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 100000

int	ft_strncmp(char *s1, char *s2, int n)
{
	int i = 0;
	while(i < n || (s1[i] && s2[i]))
	{
		if(s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return 0;
}
int main(int ac, char **av)
{
	if(ac != 2 || !av[1][0])
		return 1;
	char buffer[BUFFER_SIZE];
	char c;
	int i = 0;
	int j;
	char *pattern = av[1];
	int pattern_size = strlen(av[1]);
	int bytes_read = read(0, &c, 1);
	if(bytes_read == -1)
	{
		fprintf(stderr, "Error: ");
		perror(NULL);
		return 1;
	}
	while(bytes_read > 0)
	{
		buffer[i] = c;
		bytes_read = read(0, &c, 1);
		if(bytes_read == -1)
		{
			fprintf(stderr, "Error: ");
			perror(NULL);
			return 1;
		}
		i++;
	}
	buffer[i] = '\0';
	i = 0;
	while(buffer[i])
	{
		j = 0;
		if(!ft_strncmp(&buffer[i], pattern, pattern_size))
		{
			while(j++ < pattern_size)
				write(1, "*", 1);
			i += pattern_size;
		}
		else
		{
			write(1, &buffer[i], 1);
			i++;
		}
	}
	return (0);
}