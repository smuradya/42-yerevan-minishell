/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhakob2 <anhakob2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:25:23 by anhakob2          #+#    #+#             */
/*   Updated: 2023/03/02 20:25:23 by anhakob2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_ifs(t_cmd *tmp, char *ifs, int *i)
{
	char	*new_str;
	t_cmd	*new_elem;
	int		j;

	j = *i;
	tmp->value[*i] = '\0';
	tmp->quote[*i] = '\0';
	while (ft_strchr(ifs, tmp->value[++j]) != 0 && tmp->value[j] != '\0')
		;
	new_elem = lst_new_elem_data('w', ft_strdup(&(tmp->value[j])));
	new_elem->quote = ft_strdup(&(tmp->quote[j]));
	new_elem->next = tmp->next;
	tmp->next = new_elem;
	new_str = ft_strdup(tmp->value);
	free(tmp->value);
	tmp->value = new_str;
	new_str = ft_strdup(tmp->quote);
	free(tmp->quote);
	tmp->quote = new_str;
	return (1);
}

void	search_ifs(t_cmd **cmd, char *ifs)
{
	t_cmd	*tmp;
	int		i;

	tmp = *cmd;
	while (tmp != 0 && tmp->type != 'c')
	{
		i = -1;
		if (tmp->type != 'r' && tmp->type != 'h')
		{
			while (tmp->value[++i] != '\0')
			{
				if (tmp->value[i] == '\'' && tmp->quote[i] == '1')
					while (!(tmp->value[++i] == '\'' && tmp->quote[i] == '1'))
						;
				else if (tmp->value[i] == '\"' && tmp->quote[i] == '1')
					while (!(tmp->value[++i] == '\"' && tmp->quote[i] == '1'))
						;
				else if (ft_strchr(ifs, tmp->value[i]) != 0 && \
						tmp->quote[i] == '2' && split_ifs(tmp, ifs, &i))
					break ;
			}
		}
		tmp = tmp->next;
	}
}

void	word_splitting(t_cmd **cmd)
{
	t_node	*node;

	node = find_node_with_key(g_data->env,"IFS");
	if (node)
		search_ifs(cmd, node->value);
}
