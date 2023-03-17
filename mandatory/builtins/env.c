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

#include "../includes/minishell.h"

int	ft_env(void)
{
	print_list(g_data->env);
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

void	fill_environmental(char **arg)
{
	int		i;
	char	**tmp;
	t_node	*node;

	i = -1;
	g_data->env = new_list();
	while (arg[++i])
	{
		tmp = ft_split(arg[i], '=');
		node = new_node(tmp[0], tmp[1]);
		add(g_data->env, node);
		free_array(tmp);
		tmp = NULL;
	}
}
