/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuradya <smuradya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:00:54 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/10 19:35:39 by smuradya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_data *data)
{
	print_list(data->env);
	return (0);
}

t_node	*lst_new_elem(char *name, char *value)
{
	t_node	*new_elem;

	new_elem = (t_node *)malloc(sizeof(t_node));
	if (!new_elem)
		return (0);
	new_elem->key = name;
	new_elem->value = value;
	new_elem->next = 0;
	return (new_elem);
}

static int	for_exit_status(t_node *node, t_data **data)
{
	char	*blank;

	blank = malloc(sizeof(char) * 2);
	if (blank == 0)
		return (0);
	blank[0] = '0';
	blank[1] = '\0';
	node = lst_new_elem(ft_strdup("?"), blank);
	add((*data)->env, node);
	return (1);
}

int	fill_env(t_data **data, char **arg)
{
	int		i;
	char	**tmp;
	t_node	*node;

	i = -1;
	(*data)->env = new_list();
	while (arg[++i])
	{
		tmp = ft_split(arg[i], '=');
		node = new_node(tmp[0], tmp[1]);
		add((*data)->env, node);
		free_array(tmp);
		tmp = NULL;
	}
	return (for_exit_status(node, data));
}
