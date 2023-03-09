/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 15:06:16 by tumolabs          #+#    #+#             */
/*   Updated: 2023/03/05 15:06:17 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_node(t_node *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	node->next = NULL;
	node->prev = NULL;
	free(node);
}

static void	remove_last(t_list *list)
{
	t_node	*last;

	if (list->count == 0)
		return ;
	last = list->tail;
	if (list->count == 1)
	{
		list->tail = NULL;
		list->head = NULL;
	}
	else
		list->tail = last->prev;
	free_node(last);
	list->count--;
}

void	free_list(t_list *list)
{
	while (list->count > 0)
		remove_last(list);
	free(list);
}
