#include "minishell.h"

int	ft_signals(void)
{
	return (0);
}

void	handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_done = 1;
}

void	child_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("\n", 0);
	rl_done = 1;
}
