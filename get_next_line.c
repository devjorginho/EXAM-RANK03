#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 10

char *ft_strchr(char *s, int c)
{
  int i = 0;
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
	size_t i;

	i = 0;
	while(i < n)
	{
		d[i] = s[i];
		i++; 
	}
	return (dest);
}

size_t ft_strlen(char *s)
{
  size_t i = 0;
  while (s[i])
  	i++;
  return (i);
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t size1;
	if(*s1 == NULL)
		size1 = 0;
	else
		size1 = ft_strlen(*s1);
	char *tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return 0;
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = 0;
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
	unsigned char *d = (unsigned char *)dest;
	const unsigned char *s = (const unsigned char *)src;
	size_t i = 0;

	if(d == s || n == 0)
		return (dest);
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
	return (dest);
}

char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE + 1] = "";
	char *result = NULL;
	char *tmp = ft_strchr(buffer, '\n');
	while(!(tmp = ft_strchr(buffer, '\n')))
	{
		if (!str_append_str(&result, buffer))
			return (NULL);
		int bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			buffer[0] = 0;
			free(result);
			return (NULL);
		}
		if (bytes_read == 0)
		{
			buffer[0] = 0;
			if(result && result[0])
				return (result);
			free (result);
			return (NULL);
		}
		buffer[bytes_read] = 0;
	}
	if (!str_append_mem(&result, buffer, tmp - buffer + 1))
	{
		free(result);
		return NULL;
	}
	ft_memmove(buffer, tmp + 1, ft_strlen(tmp + 1) + 1);
	return result;
}
int main()
{
	char *line = NULL;
	int fd = open("get_next_line.c", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
}