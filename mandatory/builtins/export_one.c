/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuradya <smuradya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:52:20 by tumolabs          #+#    #+#             */
/*   Updated: 2023/03/10 17:26:51 by smuradya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_alpha(int ch)
{
	return ((ch >= 'a' && ch <= 'z')
		|| (ch >= 'A' && ch <= 'Z'));
}

int	is_numeric(int ch)
{
	return (ch >= '0' && ch <= '9');
}

int	check_for_first_character(char first)
{
	return (is_alpha(first) || first == '_');
}

int	check_for_character(char ch)
{
	return (is_alpha(ch) || is_numeric(ch) || ch == '_');
}

int	print_error(char *key)
{
	ft_putstr_fd("Minishell: export: ", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd(" :not a valid identifier\n", 2);
	return (1);
}
