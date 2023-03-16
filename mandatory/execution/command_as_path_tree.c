#include "minishell.h"

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
	t_node	*tmp;

	tmp = g_data->env->head;
	if (tmp)
	{
		while (tmp != 0)
		{
			free(tmp);
			tmp = tmp->next;
		}
	}
	free (tmp);
	free (g_data->env);
	if (g_data)
	{
		free(g_data->argument);
		free(g_data->command);
	}
	free (g_data);
}

int	free_and_exit(int exit_status)
{
	free_data();
	exit(exit_status);
}
