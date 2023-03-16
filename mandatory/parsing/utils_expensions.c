#include "minishell.h"

void	value_check(t_cmd *c, int *j)
{
	while (c->value[*j] != ' ' && c->value[*j] != '\0' && c->value[*j] != '\t'
		&& c->value[*j] != '\"' && c->value[*j] != '\'' && c->value[*j] != '/'
		&& c->value[*j] != '$' && c->value[*j] != '=')
		(*j)++;
}
