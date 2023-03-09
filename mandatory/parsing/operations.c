
#include "minishell.h"

int	operators(t_cmd *cmd)
{
	while (cmd != 0)
	{
		if (cmd->type == 'o')
		{
			if (ft_strcmp(cmd->value, ">") == 0 || \
					ft_strcmp(cmd->value, ">>") == 0 || \
					ft_strcmp(cmd->value, "<") == 0 || \
					ft_strcmp(cmd->value, "<<") == 0)
				cmd->type = 'r';
			else if (ft_strcmp(cmd->value, "|") == 0)
				cmd->type = 'c';
			else
			{
				ft_putstr_fd("Minishell: Syntax error: unexpected token '", 2);
				ft_putstr_fd(cmd->value, 2);
				ft_putstr_fd("'\n", 2);
				return (-1);
			}
		}
		cmd = cmd->next;
	}
	return (0);
}