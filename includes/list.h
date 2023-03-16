/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeghiaz <syeghiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:43:09 by tumolabs          #+#    #+#             */
/*   Updated: 2023/03/15 21:35:44 by syeghiaz         ###   ########.fr       */
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
	int		index;
	t_node	*next;
	t_node	*prev;
};

typedef struct s_list
{
	t_node	*head;
	t_node	*tail;
	int		count;
}	t_list;

struct s_data
{
	int		exit_status;
	int		**fds;
	int		fd_count;
	int		fd_to_close;
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
	char				delimitor;
	int					in;
	int					out;
	int					pipe;
	struct s_command	*next;
}						t_command;

#endif