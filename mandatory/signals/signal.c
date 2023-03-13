#include "minishell.h"

int	ft_signals(void)
{
	return (0);
}

void	handler(int sig)
{
    int  g_exit_status;
    
    g_exit_status = 0;
	(void)sig;
	rl_replace_line("", 0);
	rl_done = 1;
	g_exit_status = 26354;
}

void	child_handler(int sig)
{
    int  g_exit_status;

    g_exit_status = 0;
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("\n", 0);
	rl_done = 1;
	g_exit_status = 26354;
}

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