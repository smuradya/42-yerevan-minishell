/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_as_path_four.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuradya <smuradya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:28:29 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/18 19:28:29 by smuradya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_child(t_command *command, int child_index)
{
	t_command	*executing_command;
	int			status;
	int			count;

	count = command_count(command);
	if (dup2(g_data->fds[child_index - 1][0], STDIN_FILENO) == -1)
		free_and_exit(1);
	if (dup2(g_data->fds[child_index][1], STDOUT_FILENO) == -1)
		free_and_exit(1);
	close_fds(g_data->fds, count + 1);
	executing_command = get_command_with_index(command, child_index - 1);
	status = execute_single_command(executing_command);
	return (free_and_exit(status));
}

int	execute_child(t_command *command, int child_index, int *pid)
{
	int	status;

	status = 0;
	if (command->in == -1)
	{
		write(2, "some text here\n", 15);
		status = -1;
	}
	else
	{
		*pid = fork();
		if (*pid == -1)
			return (write(2, "some text here\n", 15));
		if (*pid == 0)
			status = command_child(command, child_index);
	}
	return (status);
}

static int	wait_for_end(int pid, int *status)
{
	waitpid(pid, status, 0);
	while (wait(NULL) != -1 || errno != ECHILD)
		;
	if (*status > 0)
		return (1);
	return (0);
}

int	execute_with_pipes(t_command *command)
{	
	t_command	*current;
	int			count;
	int			i;
	int			status;
	int			pid;

	i = 0;
	count = command_count(command);
	current = command;
	setup_redirections(command);
	while (++i <= count)
	{
		execute_child(command, i, &pid);
		current = current->next;
	}
	close_fds(g_data->fds, count + 1);
	return (wait_for_end(pid, &status));
}

int	exec_run(t_command *command)
{
	if (!command->arg || !command->arg[0])
		return (-1);
	if (!command->next)
		return (execute_single_command(command));
	else
		return (execute_with_pipes(command));
}
