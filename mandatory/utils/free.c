#include "minishell.h"

void	free_array(char **text)
{
	int	i;

	i = -1;
	if (!text)
		return ;
	while (text[++i])
		free(text[i]);
	free(text);
}

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	else
		return (c);
}

static int	contains(char *str, char ch)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ch)
			return (1);
	}
	return (0);
}

int	is_token(char ch)
{
	return (contains("()<>|&", ch));
}

int	num_len(int number)
{
	int	len;

	len = 1;
	while (number / 10 > 0)
	{
		number /= 10;
		len++;
	}
	return (len);
}
