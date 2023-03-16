/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeghiaz <syeghiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:21:40 by anhakob2          #+#    #+#             */
/*   Updated: 2023/03/15 22:29:19 by syeghiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_status(char *key, char *value)
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
