
#include "minishell.h"

void	quote_removal(t_cmd *cmd)
{
	int		i;
	char	*new_value;
	char	*new_quote;

	i = -1;
	while (cmd->value[++i] != '\0')
	{
		if ((cmd->value[i] == '\'' || cmd->value[i] == '\"') && \
				cmd->quote[i] == '1')
		{
			cmd->value[i] = '\0';
			new_value = ft_strjoin(cmd->value, cmd->value + i + 1);
			free(cmd->value);
			cmd->value = new_value;
			cmd->quote[i] = '\0';
			new_quote = ft_strjoin(cmd->quote, cmd->quote + i + 1);
			free(cmd->quote);
			cmd->quote = new_quote;
			--i;
			if (cmd->type == 'h')
				cmd->type = 'H';
		}
	}
}