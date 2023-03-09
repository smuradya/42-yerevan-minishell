/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuradya <smuradya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:00:54 by smuradya          #+#    #+#             */
/*   Updated: 2023/02/01 20:03:30 by smuradya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_data *data)
{
	print_list(data->env);
	return (0);
}


void	fill_env(t_data *data, char **arg)
{
	int		i;
	char	**tmp;
	t_node	*node;

	i = -1;
	data->env = new_list();
	while (arg[++i])
	{
		tmp = ft_split(arg[i], '=');
		node = new_node(tmp[0], tmp[1]);
		add(data->env, node);
		free_array(tmp);
		tmp = NULL;
	}
}
