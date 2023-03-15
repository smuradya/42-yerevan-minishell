/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeghiaz <syeghiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:46:43 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/15 22:09:40 by syeghiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	out_of_range(char **line)
{
	printf ("%s", "exit");
	ft_putstr_fd ("Minishell: exit: ", 2 );
	ft_putstr_fd (line[1], 2);
	ft_putstr_fd (" numeric argument required\n", 2);
	g_data->exit_status = 255;
	exit(g_data->exit_status);
}

int	is_numeric_char(char ch)
{
	return (ch >= '0' && ch <= '9');
}

int	is_numeric_argument(char *argument)
{
	int		i;
	int		len;
	int		starts_with_minus;
	size_t	number_len;

	len = ft_strlen(argument);
	starts_with_minus = argument[0] == '-';
	if (starts_with_minus && len == 1)
		return (0);
	i = -1 + starts_with_minus;
	while (argument[++i])
		if (!is_numeric_char(argument[i]))
			return (0);
	i = -1 + starts_with_minus;
	while (argument[++i] == '0')
		;
	number_len = len - i;
	if (number_len > 19 || (number_len == 19
			&& (((ft_strcmp(argument + i, "9223372036854775808") < 0)
					&& starts_with_minus)
				|| ((ft_strcmp(argument + i, "9223372036854775807") < 0)
					&& !starts_with_minus))))
		return (0);
	return (1);
}

int	ft_exit(char **line)
{
	long long	exit_status;

	if (line[1] == NULL)
	{
		printf ("exit\n");
		exit(0);
	}
	else if (!is_numeric_argument(line[1]))
	{
		return (out_of_range(line));
	}
	else if (line[2])
	{
		printf ("exit");
		ft_putstr_fd ("Minishell: exit: too many arguments\n" , 2);
		return (1);
	}
	else
	{
		printf ("exit\n");
		exit_status = ft_atoi(line[1]);
		exit (exit_status % 256);
	}
}
