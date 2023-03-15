#include "minishell.h"

void	detect_env(char *string, int *i, int *j, char *new_str)
{
	if (string[*i] != '$' || (string[*i] == '$'
			&& (!is_alpha(string[*i + 1]) && string[*i + 1] != '_'
				&& string[*i + 1] != '?')))
				new_str[++(*j)] = string[*i];
	else
		fill_from_env(string, i, new_str, j);
}

void	check_dollar(char *string, int *i, int *word_len, int *env_len)
{
	if (string[*i] != '$' || (string[*i] == '$'
			&& (!is_alpha(string[*i + 1]) && string[*i + 1] != '_'
				&& string[*i + 1] != '?')))
		(*word_len)++;
	else
	{
		*word_len += envir_len(string, *i + 1, env_len);
		*i += *env_len;
	}
}
