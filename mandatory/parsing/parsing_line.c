/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuradya <smuradya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:54:57 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/10 19:54:57 by smuradya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"  

static void	clear_all(t_command **command, t_cmd **cmd)
{
	t_command	*tmp;

	lst_clear_data(cmd, &free);
	while (*command != 0)
	{
		tmp = (*command)->next;
		command_free(*command);
		*command = tmp;
	}
}

void	parsing_line(char *line, t_cmd **cmd)
{
	int			count;
	char		metachars[11];
	t_command	*command;

	*cmd = 0;
	command = 0;
	ft_strlcpy(metachars, "<>|&;() \t\n", 11);
	count = data_count(line, metachars);
	if (count > 0)
	{
		data_array(line, metachars, cmd);
		if (operators(*cmd) == -1)
			lst_clear_data(cmd, &free);
		if (data_to_struct(cmd, &command) == 0)
			g_data->exit_status = exec_run(command);
		else
		{
			clear_all(&command, cmd);
		}
		clear_all(&command, cmd);
	}
}
