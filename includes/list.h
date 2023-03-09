/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:43:09 by tumolabs          #+#    #+#             */
/*   Updated: 2023/03/05 14:43:32 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

typedef struct s_data		t_data;
typedef struct s_command	t_command;
typedef struct s_node		t_node;
typedef char *				t_string;

struct s_node
{
	char	*key;
	char	*value;
	t_node	*next;
	t_node	*prev;
	int		index;
	int		file_error;
	int		file_status;
};

typedef struct s_list
{
	t_node	*head;
	t_node	*tail;
	int		count;
}	t_list;

struct s_data
{
	char	*argument;
	int		exit_status;
	char	*command;
	t_list	*env;
};

typedef struct s_cmd
{
	char			type;
	char			*value;
	char			*quote;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_command
{
	int					id;
	char				**arg;
	char				*oper;
	char				*oper_value;
	int					builtin;
	int					path;
	char				delimitor;
	int					std_in;
	int					std_out;
	int					pipe;
	int					pipe_out;
	int					pipe_in;
	struct s_command	*next;
}						t_command;

#endif