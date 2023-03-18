/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuradya <smuradya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:32:54 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/18 21:18:47 by smuradya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*new_list(void)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	list->count = 0;
	list->head = NULL;
	list->tail = NULL;
	return (list);
}

t_node	*new_node(char *key, char *value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->next = NULL;
	node->index = -1;
	return (node);
}

void	add(t_list *list, t_node *node)
{
	node->prev = list->tail;
	if (list->count == 0)
		list->head = node;
	else
		list->tail->next = node;
	list->tail = node;
	list->count++;
}

void	remove_with_key(t_list *list, char *key)
{
	t_node	*removing_node;

	removing_node = find_node_with_key(list, key);
	if (!removing_node)
		return ;
	if (list->count == 1)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	else if (removing_node == list->head)
		list->head = list->head->next;
	if (removing_node->next)
		removing_node->next->prev = removing_node->prev;
	if (removing_node->prev)
		removing_node->prev->next = removing_node->next;
	if (removing_node->key)
		free(removing_node->key);
	if (removing_node->value)
		free(removing_node->value);
	free(removing_node);
	list->count--;
}

void	update_with_key(t_list *list, char *key, char *new_value)
{
	t_node	*updating_node;
	char	*previous_value;

	if (!new_value)
		return ;
	updating_node = find_node_with_key(list, key);
	previous_value = updating_node->value;
	updating_node->value = ft_strdup(new_value);
	free(previous_value);
}
