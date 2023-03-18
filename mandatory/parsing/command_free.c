/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuradya <smuradya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:27:34 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/18 19:16:53 by smuradya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_free(t_command *command)
{
	int	i;

	i = -1;
	if (command)
	{
		if (command->arg)
		{
			while (command->arg[++i])
				free(command->arg[i]);
			free(command->arg);
		}
		if (command->oper)
			free(command->oper);
		if (command->oper_value)
			free(command->oper_value);
		free(command);
	}
}
