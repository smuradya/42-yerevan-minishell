/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuradya <smuradya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:27:22 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/02 14:27:22 by smuradya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	arg_del_next(t_cmd **cmd, t_cmd **tmp1, t_cmd **tmp2)
{
	if (*cmd == *tmp1)
	{
		*cmd = (*tmp1)->next;
		lst_delone_data(*tmp1, &free);
		*tmp1 = *cmd;
	}
	else
	{
		(*tmp2)->next = (*tmp1)->next;
		lst_delone_data(*tmp1, &free);
		*tmp1 = (*tmp2)->next;
	}
}

static void	arg_to_array(t_cmd **cmd, t_command *command)
{
	int		i;
	t_cmd	*tmp1;
	t_cmd	*tmp2;

	i = -1;
	tmp2 = *cmd;
	tmp1 = *cmd;
	while (tmp1 != 0 && tmp1->type != 'c')
	{
		if (tmp1->type == 'w')
		{
			command->arg[++i] = ft_strdup(tmp1->value);
			arg_del_next(cmd, &tmp1, &tmp2);
		}
		else
		{
			tmp2 = tmp1;
			tmp1 = tmp1->next;
		}
	}
}

int	arg_count(t_cmd **cmd, t_command *command)
{
	int		count;
	t_cmd	*tmp;

	tmp = *cmd;
	count = 0;
	while (tmp != 0 && tmp->type != 'c')
	{
		if (tmp->type == 'r')
		{
			tmp = tmp->next;
			if (tmp != 0 && tmp->type == 'w')
				tmp->type = 'v';
		}
		else
			count++;
		if (tmp != 0)
			tmp = tmp->next;
	}
	command->arg = (char **)malloc(sizeof(char *) * (count + 1));
	if (command->arg == 0)
		return (-1);
	command->arg[count] = 0;
	arg_to_array(cmd, command);
	return (0);
}
