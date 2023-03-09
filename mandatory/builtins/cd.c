/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:32:01 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/05 14:50:17 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_value(char *key, t_data *data)
{
	t_node	*tmp;

	tmp = data->env->head;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

void	update_oldpwd(t_data *data)
{
	char	cwd[1024];
	char	*old_pwd;

	getcwd(cwd, 1024);
	old_pwd = ft_strjoin("OLDPWD=", cwd);
	if (check_value(old_pwd, data) == 0)
		env_add(old_pwd, data);
	free(old_pwd);
}

int	ft_cd(char **args, t_data *data)
{
	update_oldpwd(data);
	t_node	*home_node;

	home_node = find_node_with_key(data->env, "HOME");
	if (!home_node)
		printf ("Minishell: cd: HOME not set\n");
	if (!args[1] || (!ft_strcmp(args[1], "~")))
		return (chdir(getenv("HOME")));
	else if (!chdir(args[1]))
		;
	else
		printf("minishell: :cd :%s No such file or directory\n", args[1]);
	return (0);
}
