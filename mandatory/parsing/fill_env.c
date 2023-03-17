/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new_elem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhakob2 <anhakob2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:58:12 by anhakob2          #+#    #+#             */
/*   Updated: 2023/01/21 19:50:29 by anhakob2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	required_word_len(char *string)
{
	int		i;
	int		env_len;
	int		word_len;

	i = -1;
	word_len = 0;
	while (string[++i])
	{
		if (string[i] == '\"' || string[i] == '\'')
			word_len += 2;
		if (string[i] == '\'')
			while (string[++i] != '\'' && string[i])
				word_len++;
		else if (string[i] == '\"')
			while (string[++(i)] != '\"' && string[i])
				check_dollar(string, &i, &word_len, &env_len);
		else
		{
			if (is_token(string[i]) && ((i > 1 && is_quote(string[i - 1], NULL))
					|| (is_quote(string[i + 1], NULL))))
				word_len++;
			check_dollar(string, &i, &word_len, &env_len);
		}
	}
	return (word_len);
}

int	envir_len(char *string, int start, int *path_len)
{
	int		i;
	char	*str;
	t_node	*node;
	char	*envir_key;

	if (string[start] == '?')
	{
		*path_len = 1;
		return (num_len(g_data->exit_status));
	}
	i = -1;
	str = string + start;
	while (str[++i] && str[i] != '\"' && is_valid_env(str[i]))
		;
	envir_key = malloc (sizeof(char) * (i + 1));
	i = -1;
	while (str[++i] && str[i] != '\"' && is_valid_env(str[i]))
		envir_key[i] = str[i];
	envir_key[i] = 0;
	*path_len = i;
	node = find_node_with_key(g_data->env, envir_key);
	free(envir_key);
	if (node == NULL)
		return (0);
	return (ft_strlen(node->value));
}

t_node	*get_env_node(char *env_var, int *e_start)
{
	int		i;
	char	*envir_key;

	i = 0;
	while (env_var[*e_start + i] && (is_numeric(env_var[*e_start + i])
			|| is_alpha(env_var[*e_start + i]) || env_var[*e_start + i] == '_'))
		i++;
	envir_key = malloc (sizeof(char) * (i + 1));
	i = 0;
	while (env_var[*e_start + i] && (is_numeric(env_var[*e_start + i])
			|| is_alpha(env_var[*e_start + i]) || env_var[*e_start + i] == '_'))
	{
		envir_key[i] = env_var[*e_start + i];
		i++;
	}
	envir_key[i] = 0;
	*e_start += (i - 1);
	return (find_node_with_key(g_data->env, envir_key));
}

void	fill_from_env(char *env_var, int *e_start, char *copy_to, int *start)
{
	int		i;
	t_node	*node;
	char	*exit_status;

	i = 0;
	++(*e_start);
	if (env_var[*e_start] == '?')
	{
		exit_status = ft_itoa(g_data->exit_status);
		i = -1;
		while (exit_status[++i])
			copy_to[*start + 1 + i] = exit_status[i];
		*start += i;
		free(exit_status);
		return ;
	}
	node = get_env_node(env_var, e_start);
	if (!node)
		return ;
	i = -1;
	while (node->value[++i])
		copy_to[*start + 1 + i] = node->value[i];
	*start += i;
}

char	*fill_env_parsing(t_string str)
{
	int		i;
	int		j;
	char	*new_str;

	i = -1;
	j = -1;
	new_str = malloc(required_word_len(str) + 1);
	iterate_str(str, new_str, &i, &j);
	new_str[++j] = 0;
	return (new_str);
}
