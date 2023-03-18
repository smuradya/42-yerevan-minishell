/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhakob2 <anhakob2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:24:23 by anhakob2          #+#    #+#             */
/*   Updated: 2023/03/02 16:24:23 by anhakob2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parsing_final(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_cmd	*tmp2;

	tmp = *cmd;
	tmp2 = tmp;
	while (tmp != 0 && tmp->type != 'c')
	{
		if (tmp2 != tmp && tmp2->type == 'r' && \
				ft_strcmp(tmp2->value, "<<") == 0)
			tmp->type = 'h';
		quote_counting(tmp);
		if (tmp->type != 'h')
			p_expansion(tmp);
		tmp2 = tmp;
		tmp = tmp->next;
	}
	word_splitting(cmd);
	tmp = *cmd;
	while (tmp != 0 && tmp->type != 'c')
	{
		if (tmp->type != 'r')
			quote_removal(tmp);
		tmp = tmp->next;
	}
}

int	parsing_command(t_cmd **cmd, t_command *command)
{
	int	i;

	parsing_final(cmd);
	arg_count(cmd, command);
	i = parsing_opers(cmd, command);
	if (i == -1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(command->oper_value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		check_status("?", "1");
	}
	if (i == -2)
	{
		g_data->exit_status = 258;
		return (-1);
	}
	if (i == -3 || i == -4)
		g_data->exit_status = 1;
	if (i < 0)
		return (-1);
	return (0);
}
