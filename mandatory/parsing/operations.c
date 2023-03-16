/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuradya <smuradya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:54:46 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/10 19:54:46 by smuradya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	operators(t_cmd *cmd)
{
	while (cmd != 0)
	{
		if (cmd->type == 'o')
		{
			if (ft_strcmp(cmd->value, ">") == 0 || \
					ft_strcmp(cmd->value, ">>") == 0 || \
					ft_strcmp(cmd->value, "<") == 0 || \
					ft_strcmp(cmd->value, "<<") == 0)
				cmd->type = 'r';
			else if (ft_strcmp(cmd->value, "|") == 0)
				cmd->type = 'c';
			else
			{
				ft_putstr_fd("Minishell: Syntax error: unexpected token '", 2);
				ft_putstr_fd(cmd->value, 2);
				ft_putstr_fd("'\n", 2);
				g_data->exit_status = 258;
				return (-1);
			}
		}
		cmd = cmd->next;
	}
	return (0);
}
