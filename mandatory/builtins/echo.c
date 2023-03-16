/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuradya <smuradya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:04:38 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/10 17:21:41 by smuradya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*writing_function(char **arg, int i)
{
	while (arg[i])
	{
		write(1, arg[i], ft_strlen(arg[i]));
		if (arg[i + 1])
			write(1, " ", 1);
		i++;
	}
	return (*arg);
}

void	check_function(char **arg, int flag, int i)
{
	if (flag == 0)
	{
		i = 1;
		writing_function(arg, i);
	}
	else if (flag == 1)
	{
		i = 2;
		writing_function(arg, i);
	}
	if (flag == 0)
		write(1, "\n", 1);
}

int	ft_echo(char **arg)
{
	int		i;
	int		flag;
	int		j;

	i = 0;
	j = 1;
	flag = 0;
	while (arg[++i])
	{
		if (ft_strncmp(arg[i], "-n", i) == 0)
			flag = 1;
		else if (arg[1][0] == '-' && arg[1][1] == 'n')
		{
			while (arg[1][++j] == 'n')
				;
			if (arg[1][j] >= 33 && arg[1][j] <= 126)
				flag = 0;
		}
		else
			break ;
	}
	check_function(arg, flag, i);
	return (0);
}
