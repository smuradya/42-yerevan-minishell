/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuradya <smuradya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:58:12 by anhakob2          #+#    #+#             */
/*   Updated: 2023/03/18 20:13:38 by smuradya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*g_data;

static int	start(int argc, char **argv, char **envp)
{
	int	g_exit_status;

	g_exit_status = 0;
	(void)argv;
	if (argc > 1)
	{
		ft_putstr_fd("More than one argument\n", 2);
		return (1);
	}
	start_signals();
	fill_environmental(envp);
	change_shlvl();
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*fill_env;
	t_cmd	*cmd;

	g_data = malloc(sizeof(t_data));
	if (start(argc, argv, envp) == 1)
		return (0);
	while (1)
	{
		line = readline_();
		if (!line)
		{
			write (1, "exit", 5);
			return (0);
		}
		if (!check_and_add_history(line))
			continue ;
		rl_catch_signals = 1;
		fill_env = fill_env_parsing(line);
		parsing_line(fill_env, &cmd);
		free (line);
		free (fill_env);
	}
	free_list(g_data->env);
}
