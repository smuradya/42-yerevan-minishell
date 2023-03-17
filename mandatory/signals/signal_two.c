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

void	start_signals(void)
{
	rl_catch_signals = 0;
	rl_event_hook = ft_signals;
	signal(SIGINT, handler);
	signal(SIGQUIT, handle_sigquit);
}
