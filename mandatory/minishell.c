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

static int	start(int argc, char **argv, char **envp, t_data *data)
{
	int	g_exit_status;

	g_exit_status = 0;
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
		free (line);
	}
}
