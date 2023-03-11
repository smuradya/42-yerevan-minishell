/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_as_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhakob2 <anhakob2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:14:56 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/10 15:28:09 by anhakob2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_path_to_command(t_string command)
{
	return (command[0] == '/' || command[0] == '.');
}

int	execute_path_as_command(t_data *data, t_string *command)
{
	if (access(command[0], F_OK | X_OK) == 0)
		return (execute_with_execve(data, command));
	else
	{
		perror (command[0]);
		return (errno);
	}
}

int	execute_with_execve(t_data *data, t_string *command)
{
	int			pid;
	t_string	*new_env;

	pid = fork();
	if (!pid)
	{
		new_env = list_to_env(data);
		if (execve(command[0], command, new_env) == -1)
		{
			data->exit_status = errno;
			perror(command[0]);
			exit (errno);
		}
	}
	wait(NULL);
	return (data->exit_status);
}

int	run_with_execve(t_command *command, t_data *data)
{
	int		pid;
	char	**new_envp;
	char	*path_to_command;

	command->path = 1;
	if (is_path_to_command(command->arg[0]))
		return (execute_path_as_command(data, command->arg));
	path_to_command = check_commands(data, command->arg[0]);
	if (path_to_command)
	{
		pid = fork();
		if (pid == 0)
		{
			new_envp = list_to_env(data);
			execve (path_to_command, command->arg, new_envp);
		}
		else
		{
			start_child_signals(0);
			wait(NULL);
		}
	}
	else
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(command->arg[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	start_signals(0);
	return (0);
}


int	exec_run(t_command *command, t_data *data)
{
	if (!command->arg || !command->arg[0])
		return (-1);
	if (is_builtin(command->arg[0]))		
		return (commands_runner(command, data));
	else
		return (run_with_execve(command, data));
}
