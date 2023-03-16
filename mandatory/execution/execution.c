/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeghiaz <syeghiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:27:04 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/15 22:16:16 by syeghiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"

static char	**split_path(void)
{
	t_node	*paths;
	char	**splitted_path;

	paths = find_node_with_key(g_data->env, "PATH");
	if (!paths)
		return (NULL);
	splitted_path = ft_split(paths->value, ':');
	return (splitted_path);
}

char	*check_commands(char *command)
{
	char	**path;
	char	*value;
	int		i;

	i = -1;
	path = split_path();
	if (!path)
		return (NULL);
	while (path[++i] != 0)
	{
		value = extra_strjoin(path[i], command, '/');
		if (access(value, F_OK | X_OK) == 0)
		{
			free_array(path);
			return (value);
		}
		free(value);
	}
	free_array(path);
	return (NULL);
}

int	is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"));
}

t_string	get_env_row(t_node *node)
{
	t_string	env_row;
	t_string	tmp;

	env_row = ft_strjoin(node->key, "=");
	if (node->value)
	{
		tmp = env_row;
		env_row = ft_strjoin(tmp, node->value);
		free(tmp);
	}
	return (env_row);
}

char	**list_to_env(void)
{
	int		i;
	char	**new_envp;
	t_node	*tmp;

	tmp = g_data->env->head;
	new_envp = malloc(sizeof(char *) * (g_data->env->count + 1));
	i = 0;
	while (tmp)
	{	
		new_envp[i] = get_env_row(tmp);
		i++;
		tmp = tmp->next;
	}
	new_envp[i] = 0;
	return (new_envp);
}
