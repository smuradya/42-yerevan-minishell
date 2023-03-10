/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_trim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 15:06:58 by tumolabs          #+#    #+#             */
/*   Updated: 2023/03/05 15:06:58 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*split_into_new_elem(char *str, t_cmd *tmp)
{
	t_cmd	*new_elem;

	new_elem = lst_new_elem_data('o', str);
	new_elem->next = tmp->next;
	return (new_elem);
}

static void	data_split(t_cmd **cmd)
{
	t_cmd	*tmp;
	char	**arr;
	int		i;

	tmp = *cmd;
	i = -1;
	while (tmp != 0)
	{
		if (tmp->type == 'o' && (ft_strchr(tmp->value, ' ') != 0))
		{
			arr = ft_split(tmp->value, ' ');
			tmp->type = 'd';
			while (arr[++i] != 0)
			{
				tmp->next = split_into_new_elem(arr[i], tmp);
				tmp = tmp->next;
			}
			if (arr != 0)
				free(arr);
		}
		tmp = tmp->next;
	}
}

static void	data_value_trim(t_cmd *cmd)
{
	char	*str;

	while (cmd != 0)
	{
		str = ft_strtrim(cmd->value, " ");
		free(cmd->value);
		cmd->value = str;
		cmd = cmd->next;
	}
}

void	data_trim(t_cmd **cmd)
{
	t_cmd	*tmp1;
	t_cmd	*tmp2;

	tmp1 = *cmd;
	data_value_trim(*cmd);
	data_split(cmd);
	while (tmp1 != 0)
	{
		if (((ft_strlen(tmp1->value) == 0) || tmp1->type == 'd') && \
				tmp1 == *cmd)
		{			
			*cmd = tmp1->next;			
			lst_delone_data(tmp1, &free);
			tmp1 = *cmd;
		}
		else if ((tmp1->next != 0) && ((ft_strlen(tmp1->next->value) == 0) || \
				tmp1->next->type == 'd'))
		{
			tmp2 = tmp1->next;
			tmp1->next = tmp1->next->next;
			lst_delone_data(tmp2, &free);
		}
		else if (tmp1 != 0)
			tmp1 = tmp1->next;
	}
}