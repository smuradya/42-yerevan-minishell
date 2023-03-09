
#include "minishell.h"  

int	parsing_line(char *line, t_cmd **cmd, t_data *data)
{
	int			count;
	char		metachars[11];
	t_command	*command;
	t_list		*list;

	list = malloc(sizeof(t_list));
	*cmd = 0;
	command = 0;
	ft_strlcpy(metachars, "<>|&;() \t\n", 11);
	count = data_count(line, metachars);
	if (count > 0)
	{
		data_array(line, metachars, cmd);
		if (operators(*cmd) == -1)
		{
			write(1, "in if\n", 6);
			lst_clear_data(cmd, &free);
			return (-1);
		}
		if (data_to_struct(cmd, &command, data) == 0)
			data->exit_status = exec_run(command, data);
	}
	return (1);
}