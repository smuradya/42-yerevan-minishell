#include "minishell.h"

int	ft_signals(void)
{
	return (0);
}

void	handler(int sig)
{
	int	g_exit_status;

	g_exit_status = 0;
	(void)sig;
	rl_replace_line("", 0);
	rl_done = 1;
	g_exit_status = 26354;
}

void	child_handler(int sig)
{
	int	g_exit_status;

	g_exit_status = 0;
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("\n", 0);
	rl_done = 1;
	g_exit_status = 26354;
}
