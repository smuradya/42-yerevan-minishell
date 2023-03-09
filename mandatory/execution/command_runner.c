/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_runner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:14:40 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/05 15:04:57 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	commands_runner(t_command *command, t_data *data)
{	
	int	exit_status;

	exit_status = 0;
	if (ft_strcmp(command->arg[0], "env") == 0)
		exit_status = ft_env(data);
	else if (ft_strcmp(command->arg[0], "export") == 0)
		exit_status = ft_export(command->arg, data);
	else if (ft_strcmp(command->arg[0], "cd") == 0)
		exit_status = ft_cd(command->arg, data);
	else if (ft_strcmp(command->arg[0], "unset") == 0)
		exit_status = ft_unset(command->arg, data);
	else if (ft_strcmp(command->arg[0], "exit") == 0)
		exit_status = ft_exit(command->arg, data);
	else if (ft_strcmp(command->arg[0], "echo") == 0)
		exit_status = ft_echo(command->arg);
	else if (ft_strcmp(command->arg[0], "pwd") == 0)
		exit_status = pwd();
	return (exit_status);
}
