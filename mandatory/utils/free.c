
#include "minishell.h"

void	free_array(char **text)
{
	int	i;

	i = -1;
	if (!text)
		return ;
	while (text[++i])
		free(text[i]);
	free(text);
}
