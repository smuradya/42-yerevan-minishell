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

int	ft_signals(void)
{
	return (0);
}

void	handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_done = 1;
}

void	child_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("\n", 0);
	rl_done = 1;
}
