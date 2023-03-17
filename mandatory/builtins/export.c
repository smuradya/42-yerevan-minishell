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

int	export_errors(char *str)
{
	int		i;
	char	**splitted;
	char	*key;
	int		has_error;

	if (str[0] == '=' || !str[0])
		return (print_error(str));
	i = 0;
	has_error = 0;
	splitted = ft_split(str, '=');
	key = splitted[0];
	if (!check_for_first_character(key[0]))
		has_error = print_error(key);
	if (!has_error)
	{
		while (key[++i])
		{
			if (!check_for_character(key[i]))
				has_error = print_error(key);
		}
	}
	free_array(splitted);
	return (has_error);
}

int	export_with_no_args(t_list *list)
{
	export_print(list);
	return (0);
}

void	node_create(char **splitted, t_node *node)
{
	if (splitted[0])
	{
		node = new_node(splitted[0], splitted[1]);
		add(g_data->env, node);
	}
}

int	ft_export(char **argument)
{
	int		i;
	t_node	*node;
	char	**splitted;
	int		has_error;

	has_error = 0;
	i = 0;
	if (!argument[1])
		return (export_with_no_args(g_data->env));
	while (argument[++i])
	{
		if (!export_errors(argument[i]))
		{
			splitted = ft_split(argument[i], '=');
			node = find_node_with_key(g_data->env, splitted[0]);
			if (node)
				update_with_key(g_data->env, splitted[0], splitted[1]);
			else
				node_create(splitted, node);
			free_array (splitted);
		}
		else
			has_error = 1;
	}
	return (has_error);
}
