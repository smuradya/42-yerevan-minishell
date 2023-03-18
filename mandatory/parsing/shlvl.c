/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuradya <smuradya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:34:30 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/18 19:34:32 by smuradya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_shlvl(void)
{
	char	*val;
	t_node	*tmp;

	tmp = g_data->env->head;
	val = NULL;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->key, "SHLVL") == 0)
		{
			val = ft_strdup(tmp->value);
			free(tmp->value);
			tmp->value = ft_itoa(ft_atoi(val) + 1);
			free(val);
			return ;
		}
		tmp = tmp->next;
	}
	free(val);
}
