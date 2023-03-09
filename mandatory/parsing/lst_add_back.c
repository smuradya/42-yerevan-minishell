/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:40:15 by anhakob2          #+#    #+#             */
/*   Updated: 2023/02/17 20:10:20 by tumolabs         ###   ########.fr       */
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


int	check_key(char *key, char *value, t_data *data)
{
	t_node	*tmp;

	tmp = data->env->head;
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

int	env_add(char *new_var, t_data *data)
{
	t_node	*new_node;
	char	**tmp;

	new_node = data->env->head;
	tmp = ft_split(new_var, '=');
	if (check_key(tmp[0], tmp[1], data) == 0)
	{
		new_node = malloc(sizeof(t_data));
		if (!(new_node))
			return (1);
		new_node->key = ft_strdup(tmp[0]);
		if (tmp[1])
			new_node->value = ft_strdup(tmp[1]);
		else
			new_node->value = NULL;
		new_node->next = NULL;
		ft_lstadd_back(&data->env->head, new_node);
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
