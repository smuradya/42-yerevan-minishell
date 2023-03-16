#include "minishell.h"

void	setup_redirections(t_command *command)
{
	int			i;
	int			count;
	t_command	*tail;

	count = command_count(command);
	g_data->fds = malloc(sizeof(int *) * (count + 1));
	g_data->fd_count = count + 1;
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

	g_data->fd_count = 0;
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

void	free_data(void)
{
	free_list(g_data->env);
	if (g_data->fd_count > 0)
		close_fds(g_data->fds, g_data->fd_count);
	free (g_data);
}

int	free_and_exit(int exit_status)
{
	free_data();
	exit(exit_status);
}
