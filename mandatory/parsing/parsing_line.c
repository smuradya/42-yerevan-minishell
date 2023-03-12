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

int	parsing_line(char *line, t_cmd **cmd, t_data *data)
{
	int			count;
	char		metachars[11];
	t_command	*command;

	*cmd = 0;
	command = 0;
	ft_strlcpy(metachars, "<>|&;() \t\n", 11);
	// if (!check_quote_syntax(line))
	// 	return (-1);
	count = data_count(line, metachars);
	if (count > 0)
	{
		data_array(line, metachars, cmd);
		if (operators(*cmd) == -1)
		{
			write(1, "in if\n", 6);
			lst_clear_data(cmd, &free);
			return (-1);
		}
		if (data_to_struct(cmd, &command, data) == 0)
			data->exit_status = exec_run(command, data);
		// printf("\n %d\n", data->exit_status);	
	}
	return (1);
}

void print_tokens(t_cmd **cmd)
{
	while(*cmd)
	{
		printf("{%c} : {%s}\n", (*cmd)->type, (*cmd)->value);
		cmd = &(*cmd)->next;
	}
}