#define _GNU_SOURCE
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

void ft_filter(char *ret, const char *target)
{
	int target_len = strlen(target);
	int i = 0;
	int j, k;
	while (ret[i])
	{
		j = 0;
		while (target[j] && ret[j + i] == target[j])
			j++;
		if (j == target_len)
		{
			k = 0;
			while (k < target_len)
			{
				write(1, "*", 1);
				k++;
			}
			i += target_len;
		}
		else 
		{
			write(1, &ret[i], 1);
			i++;
		}
	}
}
int main(int ac, char **av)
{
	if (ac != 2 || !av[1] || av[1][0] == '\0')
		return 1;

	char *b[BUFFER_SIZE];
	char *ret = NULL;
	char *temp;
	int total_ret = 0;
	ssize_t bytes;

	while ((bytes = read (0, b, BUFFER_SIZE)) > 0)
	{
		temp = realloc(ret, total_ret + bytes);
		if (!temp)
		{
			free(ret);
			perror("realloc");
			return (1);
		}
		ret = temp;
		memmove(ret + total_ret, b, bytes);
		total_ret += bytes;
		ret[total_ret] = '\0';
	}
	if (bytes < 0)
	{
		free(ret);
		perror("read");
		return (1);
	}
	if (!ret)
	{
		return (0);
	}
	ft_filter(ret,av[1]);
	free(ret);
	return (0);
}
