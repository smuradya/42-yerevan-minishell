/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new_elem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhakob2 <anhakob2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:58:12 by anhakob2          #+#    #+#             */
/*   Updated: 2023/01/21 19:50:29 by anhakob2         ###   ########.fr       */
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
	signals_init();
	// start_signals(g_exit_status);
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
		line = readline("Minishell% ");
		if (!line)
		{
			write (1, "exit", 5);
			return (0);
		}
		add_history(line);
		if (!line[0])
		{
			free(line);
			continue ;
		}
		fill_env = fill_env_parsing(line);
		if (parsing_line(fill_env, &cmd) == -1)
			continue ;
		free (line);
		free (fill_env);
		//system("leaks minishell");
	}
	free_list(g_data->env);
}
