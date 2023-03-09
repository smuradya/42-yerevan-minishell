/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expensions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 15:07:47 by tumolabs          #+#    #+#             */
/*   Updated: 2023/03/05 15:07:47 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	my_replace(t_cmd *cmd, int i, int j, t_node *node)
{
	char	*new_value;
	char	*new;
	char	*new_str;

	new_value = ft_strdup(node->value);
	cmd->value[i] = '\0';
	new_str = ft_strjoin(cmd->value, new_value);
	free(new_value);
	new_value = ft_strjoin(new_str, cmd->value + j);
	free(new_str);
	free(cmd->value);
	cmd->value = new_value;
	new = (char *)malloc(sizeof(char) * (ft_strlen(node->value) + 1));
	if (new == 0)
		return (-1);
	new[ft_strlen(node->value)] = '\0';
	ft_memset(new, '2', ft_strlen(node->value));
	cmd->quote[i] = '\0';
	new_str = ft_strjoin(cmd->quote, new);
	free(new);
	new = ft_strjoin(new_str, cmd->quote + j);
	free(new_str);
	free(cmd->quote);
	cmd->quote = new;
	return (0);
}

static int	not_found_2(t_cmd *cmd, int *i, int j, t_node *tmp)
{
	if ((j - *i) == 1 && (tmp->key[0] == '1' || \
			(cmd->value[j] != '\"' && cmd->value[j] != '\'')))
		tmp->value = (char *)malloc(sizeof(char) * 2);
	else
		tmp->value = (char *)malloc(sizeof(char) * 1);
	if (tmp->value == 0)
		return (-1);
	if ((j - *i) == 1 && (tmp->key[0] == '1' || \
			(cmd->value[j] != '\"' && cmd->value[j] != '\'')))
	{
		tmp->value[0] = '$';
		tmp->value[1] = '\0';
	}
	else
		tmp->value[0] = '\0';
	tmp->next = 0;
	return (1);
}

static int	not_found(t_cmd *cmd, int *i, int j, int quote)
{
	t_list	*tmp1;
	t_node	*tmp;
	int		res;

	tmp1 = malloc(sizeof(t_list *) * 1);
	tmp = tmp1->head;
	if (tmp == 0)
		return (-1);
	tmp->key = (char *)malloc(sizeof(char) * 2);
	if (tmp->key == 0)
		return (-1);
	if (quote == 1)
		tmp->key[0] = '1';
	else
		tmp->key[0] = '0';
	tmp->key[1] = '\0';
	not_found_2(cmd, i, j, tmp);
	res = my_replace(cmd, *i, j, tmp);
	if (!((j - *i) == 1 && (tmp->key[0] == '1' || \
			(cmd->value[j] == '\"' || cmd->value[j] == '\''))))
		*i = *i - 1;
	lst_delone(tmp, &free);
	return (res);
}

static int	search_and_replace(t_cmd *c, int *i, t_list *env, int q)
{
	char	*new_str;
	int		j;
	t_node	*tmp;

	j = *i + 1;
	tmp = env->head; 
	while (c->value[j] != ' ' && c->value[j] != '\0' && c->value[j] != '\t'
		&& c->value[j] != '\"' && c->value[j] != '\'' && c->value[j] != '/'
		&& c->value[j] != '$' && c->value[j] != '=')
		j++;
	new_str = ft_substr(c->value, *i + 1, j - *i - 1);
	while (tmp != 0)
	{
		if (ft_strncmp(tmp->key, new_str, ft_strlen(new_str) + 1) == 0)
			break ;
		tmp = tmp->next;
	}
	if (new_str[0] == '\0')
	{
		free(new_str);
		return (0);
	}
	free(new_str);
	if (tmp != 0)
		return (my_replace(c, *i, j, tmp));
	else
		return (not_found(c, i, j, q));
}

void	p_expansion(t_cmd *cmd, t_list *env)
{
	int		i;

	i = -1;
	while (cmd->value[++i] != '\0')
	{
		if (cmd->value[i] == '\'')
		{
			i++;
			while (cmd->value[i] != '\'' && cmd->value[i] != '\0')
				i++;
		}
		else if (cmd->value[i] == '\"')
		{
			while (cmd->value[++i] != '\"')
				if (cmd->value[i] == '$')
					search_and_replace(cmd, &i, env, 1);
		}
		else if (cmd->value[i] == '$')
			search_and_replace(cmd, &i, env, 0);
	}
}