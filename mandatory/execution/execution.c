/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:27:04 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/05 15:06:07 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"

static char	**split_path(t_data *data)
{
	char	*paths;
	char	**splitted_path;

	(void)data;
	paths = getenv("PATH");
	if (!paths)
		return (NULL);
	splitted_path = ft_split(paths, ':');
	return (splitted_path);
}

char	*check_commands(t_data *data, char *command)
{
	char	**path;
	char	*value;
	int		i;

	i = -1;
	path = split_path(data);
	if (!path)
		return (command);
	while (path[++i] != 0)
	{
		value = extra_strjoin(path[i], command, '/');
		if (access(value, F_OK | X_OK) == 0)
			return (value);
	}
	return (0);
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


char	**list_to_env(t_data *data)
{
	int		i;
	char	**new_envp;
	t_node	*tmp;

	tmp = data->env->head;
	new_envp = malloc(sizeof(char *) * (data->env->count + 1));
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
