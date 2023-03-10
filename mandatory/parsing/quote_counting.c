/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_counting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuradya <smuradya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:55:11 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/10 19:55:11 by smuradya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	helper(t_cmd *cmd, int *i, char c)
{
	cmd->quote[*i] = '1';
	while (cmd->value[++(*i)] != c)
		cmd->quote[*i] = '0';
	cmd->quote[*i] = '1';
}

void	quote_counting(t_cmd *cmd)
{
	int		i;

	i = -1;
	if (cmd != 0)
	{
		while (cmd->value[++i] != '\0')
		{
			if (cmd->value[i] == '\'')
				helper(cmd, &i, '\'');
			else if (cmd->value[i] == '\"')
				helper(cmd, &i, '\"');
			else
				cmd->quote[i] = '0';
		}
	}
}