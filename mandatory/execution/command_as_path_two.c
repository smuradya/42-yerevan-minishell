#include "minishell.h"

void	part_of_run_execve(t_command *command)
{
	int		pid;
	char	**new_envp;
	char	*path_to_command;

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
		part_of_run_execve(command);
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

int	command_count(t_command *command)
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
