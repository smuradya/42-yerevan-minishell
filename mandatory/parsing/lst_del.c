/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhakob2 <anhakob2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:58:39 by anhakob2          #+#    #+#             */
/*   Updated: 2023/02/10 18:04:24 by anhakob2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_delone(t_node *tmp, void (*del)(void *))
{
	if (tmp)
	{
		del(tmp->key);
		del(tmp->value);
		free (tmp);
	}
}

void	lst_delone_data(t_cmd *lst, void (*del)(void *))
{
	if (lst)
	{
		del(lst->value);
		del(lst->quote);
		free (lst);
	}
}
