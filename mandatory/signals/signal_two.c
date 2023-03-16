#include "minishell.h"

static void	handle_sigquit(int sig)
{
	(void)sig;
	rl_redisplay();
}

static void	handle_child_sigquit(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_redisplay();
}

void	start_child_signals(int g_exit_status)
{
	g_exit_status = 0;
	rl_catch_signals = 0;
	rl_event_hook = ft_signals;
	signal(SIGINT, child_handler);
	signal(SIGQUIT, handle_child_sigquit);
}

void	start_signals(int g_exit_status)
{
	g_exit_status = 0;
	rl_catch_signals = 0;
	rl_event_hook = ft_signals;
	signal(SIGINT, handler);
	signal(SIGQUIT, handle_sigquit);
}
