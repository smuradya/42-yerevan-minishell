/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuradya <smuradya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:59:00 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/10 19:57:00 by smuradya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
	start_signals(g_exit_status);
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
	// write(1, "\n", 1);
	rl_done = 1;
	g_exit_status = 26354;
}

void	child_handler(int sig)
{
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
	rl_catch_signals = 0;
	rl_event_hook = ft_signals;
	signal(SIGINT, child_handler);
	signal(SIGQUIT, handle_child_sigquit);
}

void	start_signals(int g_exit_status)
{
	rl_catch_signals = 0;
	rl_event_hook = ft_signals;
	signal(SIGINT, handler);
	signal(SIGQUIT, handle_sigquit);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmd;
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (start(argc, argv, envp, data) == 1)
		return (0);
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
		if (parsing_line(line, &cmd, data) == -1)
			continue ;
		//printf("\n %d\n", data->exit_status);
		free (line);
	}
}
