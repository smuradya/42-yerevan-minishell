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

void	detect_env(char *string, int *i, int *j, char *new_str)
{
	if (string[*i] != '$' || (string[*i] == '$'
			&& (!is_alpha(string[*i + 1]) && string[*i + 1] != '_'
				&& string[*i + 1] != '?')))
				new_str[++(*j)] = string[*i];
	else
		fill_from_env(string, i, new_str, j);
}

void	check_dollar(char *string, int *i, int *word_len, int *env_len)
{
	if (string[*i] != '$' || (string[*i] == '$'
			&& (!is_alpha(string[*i + 1]) && string[*i + 1] != '_'
				&& string[*i + 1] != '?')))
		(*word_len)++;
	else
	{
		*word_len += envir_len(string, *i + 1, env_len);
		*i += *env_len;
	}
}
