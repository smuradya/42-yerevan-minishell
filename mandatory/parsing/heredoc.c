/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuradya <smuradya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:27:53 by anhakob2          #+#    #+#             */
/*   Updated: 2023/03/18 19:29:53 by smuradya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*line_expansion(char *line)
{
	t_cmd	*tmp;
	char	*str;

	tmp = (t_cmd *)malloc(sizeof(t_cmd));
	if (tmp == 0)
		return (0);
	tmp->value = line;
	tmp->type = 'w';
	tmp->quote = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (tmp->quote == 0)
		return (0);
	tmp->quote[ft_strlen(line)] = '\0';
	tmp->quote = (char *)ft_memset(tmp->quote, '0', ft_strlen(line));
	tmp->next = 0;
	p_expansion(tmp);
	free(tmp->quote);
	str = tmp->value;
	free(tmp);
	return (str);
}

static void	go_heredoc(t_command *command, int fd_doc)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, command->oper_value,
				ft_strlen(command->oper_value) + 1) == 0)
			break ;
		if (command->delimitor == 'h')
			line = line_expansion(line);
		ft_putstr_fd(line, fd_doc);
		ft_putstr_fd("\n", fd_doc);
		free(line);
	}
	if (line != 0)
		free(line);
}

static void	heredoc_one(t_command *command, int *heredoc)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	close(heredoc[0]);
	go_heredoc(command, heredoc[1]);
	close(heredoc[1]);
	exit(0);
}

static int	heredoc_two(t_command *command, int *heredoc)
{
	int	exit_status;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	waitpid(-1, &exit_status, 0);
	close(heredoc[1]);
	if (WIFEXITED(exit_status))
	{
		exit_status = WEXITSTATUS(exit_status);
		if (exit_status == 1)
		{
			return (-3);
		}
		else
			command->in = dup(heredoc[0]);
		close(heredoc[0]);
	}
	start_child_signals();
	if (WIFSIGNALED(exit_status))
	{
		write(1, "\n", 1);
		return (-4);
	}
	return (0);
}

int	heredoc(t_command *command)
{
	int	i;
	int	pid;
	int	her[2];
	int	result;

	i = pipe(her);
	if (i == -1)
		exit(1);
	pid = fork();
	if (pid == 0)
		heredoc_one(command, her);
	else
	{
		result = heredoc_two(command, her);
		return (result);
	}
	return (0);
}
