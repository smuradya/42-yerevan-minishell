/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:49:22 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/05 15:25:00 by tumolabs         ###   ########.fr       */
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

int	ft_export(char **argument, t_data *data)
{
	int		i;
	t_node	*node;
	char	**splitted;
	int		has_error;

	has_error = 0;
	i = 0;
	if (!argument[1])
		return (export_with_no_args(data->env));
	while (argument[++i])
	{
		if (!export_errors(argument[i]))
		{
			splitted = ft_split(argument[i], '=');
			node = find_node_with_key(data->env, splitted[0]);
			if (node)
				update_with_key(data->env, splitted[0], splitted[1]);
			else
			{
				if (splitted[0])
				{
					node = new_node(splitted[0], splitted[1]);
					add(data->env, node);
				}
			}
		}
		else
			has_error = 1;
	}
	return (has_error);
}
