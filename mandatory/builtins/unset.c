/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuradya <smuradya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 20:15:46 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/10 17:05:02 by smuradya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	unset_errors(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] >= '0' && arg[i] <= '9')
		return (1);
	while (i < ft_strlen(arg))
	{
		if ((arg[i] > 32 && arg[i] < 48)
			|| (arg[i] == 58) || arg[i] == 63 || arg[i] == 59
			|| (arg[i] > 99 && arg[i] < 97)
			|| (arg[i] > 122 && arg[i] < 127) || arg[i] == 64)
			return (1);
		i++;
	}
	return (0);
}

int	ft_unset(char **cmd, t_data *data)
{
	int	i;

	i = 0;
	while (cmd[++i])
	{
		if (!unset_errors(cmd[i]))
			remove_with_key(data->env, cmd[i]);
		else
		{
			ft_putstr_fd("Minishell: unset: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(" :not a valid identifier\n", 2);
			return (1);
		}
	}
	return (0);
}
