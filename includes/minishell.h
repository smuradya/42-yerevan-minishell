/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeghiaz <syeghiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:43:42 by tumolabs          #+#    #+#             */
/*   Updated: 2023/03/15 22:35:31 by syeghiaz         ###   ########.fr       */
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


// global variable
extern t_data		*g_data;

//signals

void	start_signals(int g_exit_status);
void	start_child_signals(int g_exit_status);
void	signals_init(void);
void	handle_sigint_heredoc(int sig);


//builtins

void	print_tokens(t_cmd **cmd);
int		pwd(void);
int		is_alpha(int ch);
int		is_numeric(int ch);
int		ft_echo(char **arg);
int		ft_env(void);
int		print_error(char *key);
int		check_for_character(char ch);
int		ft_cd(char **args);
int		ft_unset(char **cmd);
int		ft_exit(char **line);
int		check_for_first_character(char first);
int		ft_export(char **argument);

// utils

int		ft_strcmp(char *s1, char *s2);
int		env_add(char *new_var);
void	fill_environmental(char **arg);
void	update_oldpwd(void);

// execution

void	change_shlvl(void);
int		is_builtin(char *cmd);
char	*execution(void);
char	**list_to_env(void);
int		exec_run(t_command *command);
char	*check_commands(char *command);
int		commands_runner(t_command *command);

// command_as_path

int		is_path_to_command(t_string command);
int		execute_with_execve(t_command *command);
int		execute_path_as_command(t_command *command);

int		heredoc(t_command *command);

//parsing

int		lst_size_data(t_cmd *lst);
t_cmd	*lst_last_data(t_cmd *lst);
void	command_free(t_command *command);
t_cmd	*lst_new_elem_data(char type, char *value);
void	lst_delone(t_node *tmp, void (*del)(void *));
void	lst_add_back_data(t_cmd **lst, t_cmd *new_node);
void	lst_delone_data(t_cmd *lst, void (*del)(void *));
void	lst_clear_data(t_cmd **lst, void (*del)(void *));
int		operators(t_cmd *cmd);
void	data_trim(t_cmd **cmd);
void	quote_removal(t_cmd *cmd);
void	quote_counting(t_cmd *cmd);
int		env_to_list(char **envp);
int		data_count(char *line, char *metachars);
void	word_splitting(t_cmd **cmd);
void	p_expansion(t_cmd *cmd);
int		arg_count(t_cmd **cmd, t_command *command);
int		check_status(char *key, char *value);
int		parsing_line(char *line, t_cmd **cmd);
void	data_array(char *line, char *metachars, t_cmd **cmd);
int		parsing_opers(t_cmd **cmd, t_command *command);
int		data_to_struct(t_cmd **cmd, t_command **command);
int		parsing_command(t_cmd **cmd, t_command *command);

// fill_env.c
char	*fill_env_parsing(t_string str);
int		required_word_len(char *string);
int		envir_len(char *string, int start, int *path_len);
void	fill_from_env(char *env_var, int *e_start, char *copy_to, int *start);

// clearing_quotes_utils.c

void	detect_env(char *string, int *i, int *j, char *new_str);
void	check_dollar(char *string, int *i, int *word_len, int *env_len);

// preprocessing_utils.c
int		is_space(char chr);
int		is_valid_env(char ch);
int		is_quote(char ch, char *quote);
void	iterate_str(t_string str, t_string new_str, int *i, int *j);

int		is_token(char ch);
int		num_len(int number);


// smart_split
char	**smart_split(t_string str);

#endif