/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuradya <smuradya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 20:08:46 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/18 20:09:24 by smuradya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_printable(char ch)
{
	return (ch <= 31);
}

char	*readline_(void)
{
	char	*line;

	start_signals();
	rl_catch_signals = 0;
	line = readline("Minishell% ");
	return (line);
}

int	check_and_add_history(char *line)
{
	add_history(line);
	if (!line[0] || not_printable(line[0]))
	{
		free(line);
		return (0);
	}
	return (1);
}
