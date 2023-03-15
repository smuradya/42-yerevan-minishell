/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhakob2 <anhakob2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:24:32 by anhakob2          #+#    #+#             */
/*   Updated: 2023/03/02 16:24:32 by anhakob2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parsing_ins(t_command *command)
{
	int	fd;

	if (ft_strncmp(command->oper, "<", 2) == 0)
	{
		fd = open(command->oper_value, O_RDONLY);
		if (fd < 0)
		{
			command->in = -1;
			return (-1);
		}
		if (command->in != 0)
			close(command->in);
		command->in = fd;
	}
	else if (ft_strncmp(command->oper, "<<", 3) == 0)
		return (heredoc(command));
	return (0);
}

static void	parsing_out(t_command *command)
{
	int	fd;

	fd = open(command->oper_value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (command->out != 1)
		close(command->out);
	command->out = fd;
}

static int	parsing_redirs(t_cmd **cmd, t_command *command, t_cmd **tmp)
{
	int	fd;

	if (command->oper_value != 0)
		free(command->oper_value);
	command->oper_value = ft_strdup((*cmd)->value);
	command->delimitor = (*cmd)->type;
	*tmp = *cmd;
	*cmd = (*cmd)->next;
	lst_delone_data(*tmp, &free);
	if (ft_strncmp(command->oper, ">", 2) == 0)
	{
		fd = open(command->oper_value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (command->out != 1)
			close(command->out);
		command->out = fd;
	}
	else if (ft_strncmp(command->oper, ">>", 3) == 0)
		parsing_out(command);
	else
		return (parsing_ins(command));
	return (0);
}

int	parsing_opers(t_cmd **cmd, t_command *command)
{
	t_cmd	*tmp;
	int		status;

	status = 0;
	while ((*cmd) != 0 && (*cmd)->type != 'c' && status >= 0)
	{
		if (command->oper != 0)
			free(command->oper);
		command->oper = ft_strdup((*cmd)->value);
		tmp = *cmd;
		*cmd = (*cmd)->next;
		lst_delone_data(tmp, &free);
		if (*cmd != 0 && ((*cmd)->type == 'v'
				|| (*cmd)->type == 'h' || (*cmd)->type == 'H'))
			status = parsing_redirs(cmd, command, &tmp);
		else
		{
			ft_putstr_fd("Minishell$ Syntax error: Undefined value after " \
					"operator\n", 2);
			return (-2);
		}
	}
	return (status);
}
