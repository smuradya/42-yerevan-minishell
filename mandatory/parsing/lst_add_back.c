/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeghiaz <syeghiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:40:15 by anhakob2          #+#    #+#             */
/*   Updated: 2023/03/15 22:21:59 by syeghiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_node	*ft_lstlast(t_node *node)
{
	if (node == 0)
		return (0);
	while (node->next)
		node = node->next;
	return (node);
}

void	ft_lstadd_back(t_node **node, t_node *new)
{
	t_node	*lst;

	lst = *node;
	if (!lst)
	{
		*node = new;
		return ;
	}
	lst = ft_lstlast(*node);
	lst->next = new;
}

int	check_key(char *key, char *value)
{
	t_node	*tmp;

	tmp = g_data->env->head;
	if (!key)
		return (0);
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			if (!value)
			{
				tmp->value = NULL;
				return (1);
			}
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	env_add(char *new_var)
{
	t_node	*new_node;
	char	**tmp;

	new_node = g_data->env->head;
	tmp = ft_split(new_var, '=');
	if (check_key(tmp[0], tmp[1]) == 0)
	{
		new_node = malloc(sizeof(t_node));
		if (!(new_node))
			return (1);
		new_node->key = ft_strdup(tmp[0]);
		if (tmp[1])
			new_node->value = ft_strdup(tmp[1]);
		else
			new_node->value = NULL;
		new_node->next = NULL;
		add(g_data->env, new_node);
	}
	free_array(tmp);
	return (0);
}

void	lst_add_back_data(t_cmd **lst, t_cmd *new_node)
{
	t_cmd	*tmp;

	if (lst)
	{
		if (*lst == 0)
			*lst = new_node;
		else
		{
			tmp = lst_last_data(*lst);
			tmp->next = new_node;
		}
	}
}
