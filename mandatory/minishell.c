
#include "minishell.h"

int	g_exit_status = 0;

static int	start(int argc, char **argv, char **envp, t_data *data)
{
	(void)argv;
	if (argc > 1)
	{
		ft_putstr_fd("More than one argument\n", 2);
		return (1);
	}
	// start_signal(g_exit_status);
	fill_env(data, envp);
	change_shlvl(data);
	return (0);
}


int	ft_signals(void)
{
	return (0);
}

void	handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_done = 1;
	g_exit_status = 26354;
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmd;
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (start(argc, argv, envp, data) == 1)
		return (0);
	cmd = malloc(sizeof(t_cmd));
	rl_catch_signals = 0;
	rl_event_hook = ft_signals;
	signal(SIGINT, &handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("Minishell% ");
		if (!line)
		{
			write (1, "exit", 5);
			return (0);
		}
		add_history(line);
		if (!line[0])
			continue ;
		parsing_line(line, &cmd, data);
		//printf("\n %d\n", data->exit_status);
		free (line);
	}
}