/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new_elem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhakob2 <anhakob2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:58:12 by anhakob2          #+#    #+#             */
/*   Updated: 2023/01/21 19:50:29 by anhakob2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **text)
{
	int	i;

	i = -1;
	if (!text)
		return ;
	while (text[++i])
		free(text[i]);
	free(text);
}

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	else
		return (c);
}

static int	contains(char *str, char ch)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ch)
			return (1);
	}
	return (0);
}

int	is_token(char ch)
{
	return (contains("()<>|&", ch));
}

int	num_len(int number)
{
	int	len;

	len = 1;
	while (number / 10 > 0)
	{
		number /= 10;
		len++;
	}
	return (len);
}
