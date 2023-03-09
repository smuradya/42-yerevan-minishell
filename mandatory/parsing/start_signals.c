
// #include "minishell.h"

// int	ft_signals(void)
// {
// 	return (0);
// }

// void	handler(int sig)
// {
// 	(void)sig;
// 	rl_replace_line("", 0);
// 	rl_done = 1;
// 	g_exit_status = 26354;
// }

// void	start_signals(int g_exit_status)
// {
// 	rl_catch_signals = 0;
// 	rl_event_hook = ft_signals;
// 	signal(SIGINT, &handler);
// 	signal(SIGQUIT, SIG_IGN);
// }
