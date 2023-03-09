/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 15:06:28 by tumolabs          #+#    #+#             */
/*   Updated: 2023/03/05 15:06:29 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*find_node_with_key(t_list *list, char *key)
{
	t_node	*node;

	if (!key)
		return (NULL);
	if (list->count <= 0)
		return (NULL);
	node = list->head;
	while (node)
	{
		if (!ft_strcmp(key, node->key))
			return (node);
		node = node->next;
	}
	return (NULL);
}

void	for_each(t_list *list, void (*func)(t_node *))
{
	int		i;
	t_node	*current;

	i = -1;
	current = list->head;
	while (++i < list->count)
	{
		func(current);
		current = current->next;
	}
}

void	unset_index(t_node *node)
{
	node->index = -1;
}
