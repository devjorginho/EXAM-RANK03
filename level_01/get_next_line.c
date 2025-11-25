#define BUFFER_SIZE 10
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

char *ft_strchr(char *s, int c)
{
	int i = 0;
	if(!s)
		return NULL;
	while(s[i])
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	return NULL;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	char *d = (char *)dest;
	const char *s = (const char *)src;
	size_t i = 0;

	while(i < n)
	{
		d[i] = s[i];
		i++;
	}
	return dest;
}

size_t ft_strlen(char *s)
{
	size_t i = 0;
	while (s[i])
		i++;
	return i;
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t size1;
	if(!*s1)
		size1 = 0;
	else
		size1 = ft_strlen(*s1);
	char *tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return 0;
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	free(*s1);
	*s1 = tmp;
	return 1; 
}

int str_append_str(char **s1, char *s2)
{
	return str_append_mem(s1, s2, ft_strlen(s2));
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
	char *d = (char *)dest;
	const char *s = (const char *)src;
	size_t i = 0;

	if(d == s || n == 0)
		return dest;
	if(d > s)
	{
		while(n > i)
		{
			n--;
			d[n] = s[n];
		}
	}
	else
		ft_memcpy(dest, src, n);
	return dest;
}

char *get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;
	char *tmp = ft_strchr(b, '\n');
	while(!((tmp = ft_strchr(b, '\n'))))
	{
		if (!str_append_str(&ret, b))
			return (NULL);
		int read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
		{
			b[0] = 0;
			free(ret);
			return (NULL);
		}
		if (read_ret == 0)
		{
			b[0] = 0;
			if(ret && ret[0])
				return (ret);
			free(ret);
			return (NULL);
		}
		b[read_ret] = 0;
	}
	if (!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return NULL;
	}
	ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);
	return ret;
}

int main()
{
	int fd = open("filter.c", O_RDONLY);
	char *line = get_next_line(fd);
	while(line)
	{
		printf("%s", line);
		if(line)
			free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}