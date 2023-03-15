/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_to_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhakob2 <anhakob2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:23:24 by anhakob2          #+#    #+#             */
/*   Updated: 2023/03/02 16:23:24 by anhakob2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	command_init(t_command **command)
{
	(*command) = (t_command *)malloc(sizeof(t_command));
	(*command)->id = 0;
	(*command)->arg = 0;
	(*command)->oper = 0;
	(*command)->oper_value = 0;
	(*command)->in = 0;
	(*command)->out = 1;
	(*command)->pipe = 0;
	(*command)->next = 0;
}

static int	parsing_pipe(t_cmd **cmd, t_command *last)
{
	t_cmd		*tmp;
	t_command	*new_command;
	int			fd[2];

	last->pipe = 1;
	tmp = *cmd;
	*cmd = (*cmd)->next;
	lst_delone_data(tmp, &free);
	if (pipe(fd) == -1)
		return (-1);
	command_init(&new_command);
	last->next = new_command;
	return (0);
}

int	data_to_struct(t_cmd **cmd, t_command **command)
{
	t_command	*last;
	int			id;

	id = 0;
	command_init(command);
	if (parsing_command(cmd, *command) == -1)
		return (-1);
	(*command)->id = id;
	while ((*cmd) != 0 && ft_strcmp((*cmd)->value, "|") == 0)
	{
		last = *command;
		while (last->next != 0)
			last = last->next;
		parsing_pipe(cmd, last);
		last = *command;
		while (last->next != 0)
			last = last->next;
		if (parsing_command(cmd, last) == -1)
			return (-1);
		last->id = ++id;
	}
	return (0);
}
