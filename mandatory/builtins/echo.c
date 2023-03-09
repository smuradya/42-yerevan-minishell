/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:04:38 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/05 14:50:29 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo(char **arg)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (arg[++i])
	{
		if (ft_strncmp(arg[i], "-n", i) == 0)
			flag = 1;
		else if (arg[1][0] == '-' && arg[1][1] == 'n')
		{
			int j = 1;
			while (arg[1][++j] == 'n')
				;
			if (arg[1][j] >= 33 && arg[1][j] <= 126)
				flag = 0;
		}
		else
			break ;
	}
	if (flag == 0)
	{
		i = 1;
		while (arg[i])
		{
			write(1, arg[i], ft_strlen(arg[i]));
			if (arg[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	else if (flag == 1)
	{
		i = 2;
		while (arg[i])
		{
			write(1, arg[i], ft_strlen(arg[i]));
			if (arg[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (flag == 0)
		write(1, "\n", 1);
	return (0);
}
