/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuradya <smuradya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:27:46 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/02 14:27:46 by smuradya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	word_malloc(t_cmd **cmd, int *j, size_t *word_len, char *line)
{
	t_cmd	*cmd_elem;
	char	*str;

	if (line != 0 && *word_len != 0)
	{
		str = (char *)malloc(sizeof(char) * (*word_len + 1));
		ft_strlcpy(str, line, *word_len + 1);
		if (ft_strchr("<>|&;() \t\n", str[0]) != 0)
			cmd_elem = lst_new_elem_data('o', str);
		else
			cmd_elem = lst_new_elem_data('w', str);
		lst_add_back_data(cmd, cmd_elem);
		(*j)++;
		line = 0;
		*word_len = 0;
	}
}

static char	*single_quotes(char *line, int *i, size_t *word, char *metachars)
{
	if (line[*i] == '\'')
	{
		(*word)++;
		(*i)++;
		while (line[*i] != '\'' && line[*i] != '\0')
		{
			(*word)++;
			(*i)++;
		}
		(*word)++;
		(*i)++;
		if (line[*i] == '\0' || ft_strchr(metachars, line[*i]) != 0)
			return (line + *i - *word);
	}
	return (0);
}

static char	*double_quotes(char *line, int *i, size_t *word, char *metachars)
{
	if (line[*i] == '\"')
	{
		(*word)++;
		(*i)++;
		while (line[*i] != '\"' && line[*i] != '\0')
		{
			(*word)++;
			(*i)++;
		}
		(*word)++;
		(*i)++;
		if (line[*i] == '\0' || ft_strchr(metachars, line[*i]) != 0)
			return (line + *i - *word);
	}
	return (0);
}

static char	*words_and_ops(char	*line, int *i, size_t *word, char *metachars)
{
	if (ft_strchr(metachars, line[*i]) != 0 && line[*i] != '\0')
	{
		while (ft_strchr(metachars, line[*i]) != 0 && line[*i] != '\0')
		{
			(*word)++;
			(*i)++;
		}
		return (line + *i - *word);
	}
	else if (line[*i] != '\'' && line[*i] != '\"' && line[*i] != '\0')
	{
		while (ft_strchr(metachars, line[*i]) == 0 && \
				line[*i] != '\0' && line[*i] != '\'' && line[*i] != '\"')
		{
			(*word)++;
			(*i)++;
		}
		if ((line[*i] != '\'' && line[*i] != '\"') || line[*i] == '\0')
			return (line + *i - *word);
	}
	return (0);
}

void	data_array(char *line, char *metachars, t_cmd **cmd)
{
	int		i;
	int		j;
	size_t	word_len;
	char	*start;

	i = 0;
	j = 0;
	word_len = 0;
	while (line[i] != '\0')
	{
		start = single_quotes(line, &i, &word_len, metachars);
		word_malloc(cmd, &j, &word_len, start);
		start = double_quotes(line, &i, &word_len, metachars);
		word_malloc(cmd, &j, &word_len, start);
		start = words_and_ops(line, &i, &word_len, metachars);
		word_malloc(cmd, &j, &word_len, start);
	}
	data_trim(cmd);
}

//      sdfsd "adfsdf dfsdfsd"