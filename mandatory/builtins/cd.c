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

#include "../includes/minishell.h"

char	*check_value(char *key)
{
	t_node	*tmp;

	tmp = g_data->env->head;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

void	update_oldpwd(void)
{
	char	cwd[1024];
	char	*old_pwd;

	getcwd(cwd, 1024);
	old_pwd = ft_strjoin("OLDPWD=", cwd);
	if (check_value(old_pwd) == 0)
		env_add(old_pwd);
	free(old_pwd);
}

int	ft_cd(char **args)
{
	int		has_error;
	t_node	*home_node;

	update_oldpwd();
	has_error = 0;
	home_node = find_node_with_key(g_data->env, "HOME");
	if (!home_node)
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
		has_error = 1;
	}
	if (!args[1] || (!ft_strcmp(args[1], "~")))
		return (chdir(getenv("HOME")));
	else if (!chdir(args[1]))
		;
	else
	{
		ft_putstr_fd("minishell: :cd ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(" :No such file or directory\n", 2);
		has_error = 1;
	}
	return (has_error);
}
