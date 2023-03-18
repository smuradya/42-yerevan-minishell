/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuradya <smuradya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:58:12 by anhakob2          #+#    #+#             */
/*   Updated: 2023/03/18 19:29:17 by smuradya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	start_child_signals(void)
{
	signal(SIGINT, child_handler);
	signal(SIGQUIT, handle_child_sigquit);
}

void	start_signals(void)
{
	rl_event_hook = ft_signals;
	signal(SIGINT, handler);
	signal(SIGQUIT, handle_sigquit);
}

void	start_heredoc_signals(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handle_sigquit);
}
