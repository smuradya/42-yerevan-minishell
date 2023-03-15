#include "minishell.h"

int	get_arguments_count(char *str)
{
	int		count;
	int		i;
	char	quote;

	i = -1;
	count = 1;
	while (is_space(str[++i]))
		;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (is_quote(str[i], &quote))
			while (str[++i] != quote)
				;
		else if (is_space(str[i]) && str[i + 1]
			&& !is_space(str[i + 1]))
			count++;
		i++;
	}
	return (count);
}

char	*fill_word(char *str, int start, int len)
{
	char	*word;
	int		i;

	i = -1;
	word = malloc(sizeof(char) * (len + 1));
	while (++i < len)
		word[i] = str[start + i];
	word[len] = 0;
	return (word);
}

void	fill_word_checking(char *fill_from, int *end, char quote)
{
	(*end)++;
	while (fill_from[*end] != quote)
		(*end)++;
}

char	**fill_words_array(int arguments_count, char *fill_from)
{
	char	**result;
	int		index;
	int		start;
	int		end;
	char	quote;

	start = -1;
	index = -1;
	result = malloc(sizeof(char *) * (arguments_count + 1));
	while (++index < arguments_count)
	{
		while (is_space(fill_from[++start]))
			;
		end = start;
		while (fill_from[end] && !is_space(fill_from[end]))
		{
			if (is_quote(fill_from[end], &quote))
				fill_word_checking(fill_from, &end, quote);
			end++;
		}
		result[index] = fill_word(fill_from, start, end - start);
		start = end;
	}
	result[index] = NULL;
	return (result);
}

char	**smart_split(t_string str)
{
	t_string	filled_with_env;
	t_string	*result;
	int			arguments_count;

	filled_with_env = fill_env_parsing(str);
	arguments_count = get_arguments_count(filled_with_env);
	result = fill_words_array(arguments_count, filled_with_env);
	free(filled_with_env);
	return (result);
}
