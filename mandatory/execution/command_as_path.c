/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_as_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuradya <smuradya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:32:02 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/18 19:32:05 by smuradya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_path_to_command(t_string command)
{
	return (command[0] == '/' || command[0] == '.');
}

void	handle_redirections(t_command *command)
{
	dup2(command->out, 1);
	dup2(command->in, 0);
}

void	reset_redirections(t_command *command)
{
	dup2(1, command->out);
	dup2(0, command->in);
}

int	execute_path_as_command(t_command *command)
{
	if (access(command->arg[0], F_OK | X_OK) == 0)
		return (execute_with_execve(command));
	else
	{
		perror (command->arg[0]);
		return (errno);
	}
}

int	execute_with_execve(t_command *command)
{
	int			pid;
	t_string	*new_env;

	pid = fork();
	if (!pid)
	{
		new_env = list_to_env();
		if (execve(command->arg[0], command->arg, new_env) == -1)
		{
			g_data->exit_status = errno;
			perror(command->arg[0]);
			exit (errno);
		}
	}
	wait(NULL);
	return (g_data->exit_status);
}
