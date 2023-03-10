/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuradya <smuradya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:43:42 by tumolabs          #+#    #+#             */
/*   Updated: 2023/03/10 17:51:31 by smuradya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "list.h"
# include "utils.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include "linkedlist.h"
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>

//signals

void	start_signals(int g_exit_status);

//builtins
void	print_tokens(t_cmd **cmd);
int		pwd(void);
int		is_alpha(int ch);
int		is_numeric(int ch);
int		ft_echo(char **arg);
int		ft_env(t_data *data);
int		print_error(char *key);
int		check_for_character(char ch);
int		ft_cd(char **args, t_data *env);
int		ft_unset(char **cmd, t_data *env);
int		ft_exit(char **line, t_data *data);
int		check_for_first_character(char first);
int		ft_export(char **argument, t_data *data);

// utils
int		ft_strcmp(char *s1, char *s2);
int		env_add(char *new_var, t_data *data);
void	fill_env(t_data *data, char **arg);
void	update_oldpwd(t_data *data);
// execution

void	change_shlvl(t_data *data);
int		is_builtin(char *cmd);
char	*execution(t_data *data);
char	**list_to_env(t_data *envv);
int		exec_run(t_command *command, t_data *data);
char	*check_commands(t_data *data, char *command);
int		commands_runner(t_command *command, t_data *data);

// command_as_path

int		is_path_to_command(t_string command);
int		execute_with_execve(t_data *data, t_string *command);
int		execute_path_as_command(t_data *data, t_string *command);

//parsing

int		lst_size_data(t_cmd *lst);
t_cmd	*lst_last_data(t_cmd *lst);
void	command_free(t_command *command);
t_cmd	*lst_new_elem_data(char type, char *value);
void	lst_delone(t_node *tmp, void (*del)(void *));
void	lst_add_back_data(t_cmd **lst, t_cmd *new_node);
void	lst_delone_data(t_cmd *lst, void (*del)(void *));
void	lst_clear_data(t_cmd **lst, void (*del)(void *));

void	signals_init(void);
void	handle_sigint_heredoc(int sig);
int		heredoc(t_command *command, t_list **env);

int		operators(t_cmd *cmd);
void	data_trim(t_cmd **cmd);
void	quote_removal(t_cmd *cmd);
void	quote_counting(t_cmd *cmd);
int		env_to_list(char **envp, t_list *env);
int		data_count(char *line, char *metachars);
void	word_splitting(t_cmd **cmd, t_list *env);
void	p_expansion(t_cmd *cmd, t_list *list);
int		arg_count(t_cmd **cmd, t_command *command);
int		check_status(char *key, char *value, t_data *data);
int		parsing_line(char *line, t_cmd **cmd, t_data *data);
void	data_array(char *line, char *metachars, t_cmd **cmd);
int		parsing_opers(t_cmd **cmd, t_command *command, t_list **env);
int		data_to_struct(t_cmd **cmd, t_command **command, t_data *data);
int		parsing_command(t_cmd **cmd, t_command *command, t_data *data);

#endif