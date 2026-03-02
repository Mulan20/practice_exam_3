#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return i;
}

int	ft_isalpha(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int	ft_strchr(char *s, char c)
{
	int i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return 1;
		i++;
	}
	return 0;
}

char	*ft_sort(char *s)
{
	int i = 0;
	while (s[i])
	{
		if (s[i + 1] && s[i] > s[i + 1])
		{
			char tmp = s[i];
			s[i] = s[i + 1];
			s[i + 1] = tmp;
			i = 0;
		}
		else
		i++;
	}
	return s;
}

void	permute(char *src, char *res, int pos)
{
	int len;
	int i;

	len = ft_strlen(src);
	if (pos == len)
	{
		write(1, res, len);
		write(2, "\n", 1);
		return ;
	}

	i = 0;
	while (i < len)
	{
		if (!ft_strchr(res, src[i]))
		{
			res[pos] = src[i];
			permute(src, res, pos + 1);
			res[pos] = '\0';
		}
		i++;
	}
}

int main(int ac, char **av)
{
	if (ac != 2)
		return 1;
	int len = ft_strlen(av[1]);
	if (len == 0 || (av[1][0] == ' ' && !av[1][1]))
		return 1;

	int i = 0;
	while (av[1][i])
	{
		if (!ft_isalpha(av[1][i]))
			return 1;
		i++;
	}

	char *result = calloc(len + 1, 1);
	if (!result)
		return 1;

	char *sorted_str = ft_sort(av[1]);

	permute(sorted_str, result, 0);
	free(result);
	return 0;
}
