/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_last.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhakob2 <anhakob2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:54:10 by anhakob2          #+#    #+#             */
/*   Updated: 2023/03/10 15:18:11 by anhakob2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*lst_last_data(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		return (tmp);
	}
	return (0);
}
