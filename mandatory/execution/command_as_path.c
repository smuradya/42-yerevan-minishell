/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_as_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeghiaz <syeghiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:14:56 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/15 22:15:28 by syeghiaz         ###   ########.fr       */
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

int	run_with_execve(t_command *command)
{
	int		pid;
	char	**new_envp;
	char	*path_to_command;

	if (is_path_to_command(command->arg[0]))
		return (execute_path_as_command(command));
	path_to_command = check_commands(command->arg[0]);
	if (path_to_command)
	{
		pid = fork();
		if (pid == 0)
		{
			handle_redirections(command);
			new_envp = list_to_env();
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

int command_count(t_command *command)
{
	int			count;
	t_command	*temp;

	count = 0;
	temp = command;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

void	close_fds(int **fds, int i_len)
{
	int	i;

	i = -1;
	while (++i < i_len)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		free(fds[i]);
	}
	free(fds);
}


t_command	*get_tail(t_command *first_command)
{
	t_command	*temp;

	temp = first_command;
	while (temp->next)
		temp = temp->next;
	return (temp);
}


void	setup_redirections(t_command *command)
{
	int			i;
	int			count;
	t_command	*tail;

	count = command_count(command);
	g_data->fds = malloc(sizeof(int *) * (count + 1));
	i = -1;
	while (++i < count + 1)
		g_data->fds[i] = (int *)malloc(sizeof(int) * 2);
	i = -1;
	while (++i < count + 1)
		pipe(g_data->fds[i]);
	if (command->in != -1)
		dup2(command->in, g_data->fds[0][0]);
	dup2(get_tail(command)->out, g_data->fds[count][1]);
}

int	execute_single_command(t_command *command)
{
	int	std_out;
	int	std_in;
	int	status;

	printf("command->in = %d, command->out = %d\n", command->in, command->out);
	if (is_builtin(command->arg[0]))
	{
		std_out = dup(STDOUT_FILENO);
		std_in = dup(STDIN_FILENO);
		handle_redirections(command);
		status = commands_runner(command);
		dup2(std_out, 1);
		dup2(std_in, 0);
		return (status);
	}
	else
		return (run_with_execve(command));
}	

t_command	*get_command_with_index(t_command *first, int index)
{
	t_command	*command;
	int			i;

	i = -1;
	command = first;
	while (++i < index && command->next)
		command = command->next;
	return (command);
}


void	free_data()
{
	write(1, "FREE DATA!!!", 12);
}

int	free_and_exit(int exit_status)
{
	exit(exit_status);
}


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
