/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 15:09:04 by tumolabs          #+#    #+#             */
/*   Updated: 2023/03/05 15:09:06 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_clear(void)
{
	t_node	*tmp;

	tmp = g_data->env->head;
	if (g_data->env->head)
	{
		while (g_data->env->head != 0)
		{
			tmp = g_data->env->head->next;
			free(g_data->env->head);
			g_data->env->head = tmp;
		}
	}
	free (g_data->env->head);
	free (g_data->env);
	if (g_data)
	{
		free(g_data->argument);
		free(g_data->command);
	}
	free (g_data);
}

void	lst_clear_data(t_cmd **lst, void (*del)(void *))
{
	t_cmd	*tmp;

	if (lst != 0 && *lst != 0)
	{
		while (*lst != 0)
		{
			tmp = (*lst)->next;
			lst_delone_data(*lst, del);
			*lst = tmp;
		}
	}
}
