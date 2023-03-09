#include "minishell.h"

void	change_shlvl(t_data *data)
{
	char	*val;
	t_node	*tmp;

	tmp = data->env->head;
	val = NULL;

	while (tmp->next)
	{
		if (ft_strcmp(tmp->key, "SHLVL") == 0)
		{
			val = ft_strdup(tmp->value);
			free(tmp->value);
			tmp->value = ft_itoa(ft_atoi(val) + 1);
			free(val);
			return ;
		}
		tmp = tmp->next;
	}
}