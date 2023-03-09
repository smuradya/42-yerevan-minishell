
#include "minishell.h"

static void	helper(t_cmd *cmd, int *i, char c)
{
	cmd->quote[*i] = '1';
	while (cmd->value[++(*i)] != c)
		cmd->quote[*i] = '0';
	cmd->quote[*i] = '1';
}

void	quote_counting(t_cmd *cmd)
{
	int		i;

	i = -1;
	if (cmd != 0)
	{
		while (cmd->value[++i] != '\0')
		{
			if (cmd->value[i] == '\'')
				helper(cmd, &i, '\'');
			else if (cmd->value[i] == '\"')
				helper(cmd, &i, '\"');
			else
				cmd->quote[i] = '0';
		}
	}
}