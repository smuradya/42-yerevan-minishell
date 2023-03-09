/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:52:20 by tumolabs          #+#    #+#             */
/*   Updated: 2023/03/05 15:24:33 by tumolabs         ###   ########.fr       */
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
	printf("Minishell: export: `%s': not a valid identifier\n", key);
	return (1);
}
