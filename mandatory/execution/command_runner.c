/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_runner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuradya <smuradya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:32:14 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/18 19:32:17 by smuradya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	commands_runner(t_command *command)
{	
	int	exit_status;

	exit_status = g_data->exit_status;
	if (ft_strcmp(command->arg[0], "env") == 0)
		exit_status = ft_env();
	else if (ft_strcmp(command->arg[0], "export") == 0)
		exit_status = ft_export(command->arg);
	else if (ft_strcmp(command->arg[0], "cd") == 0)
		exit_status = ft_cd(command->arg);
	else if (ft_strcmp(command->arg[0], "unset") == 0)
		exit_status = ft_unset(command->arg);
	else if (ft_strcmp(command->arg[0], "exit") == 0)
		exit_status = ft_exit(command->arg);
	else if (ft_strcmp(command->arg[0], "echo") == 0)
		exit_status = ft_echo(command->arg);
	else if (ft_strcmp(command->arg[0], "pwd") == 0)
		exit_status = pwd();
	return (exit_status);
}
