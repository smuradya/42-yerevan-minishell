/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuradya <smuradya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:30:28 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/18 19:30:30 by smuradya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKEDLIST_H
# define LINKEDLIST_H

// linkedlist.c
t_list	*new_list(void);
void	add(t_list *list, t_node *node);
t_node	*new_node(char *key, char *value);
void	remove_with_key(t_list *list, char *key);
void	update_with_key(t_list *list, char *key, char *new_value);

// linkedlist_utils.c
t_node	*find_node_with_key(t_list *list, char *key);
void	for_each(t_list *list, void (*func)(t_node *));

// linkedlist_free.c
void	free_list(t_list *list);
void	unset_index(t_node *node);

// linkedlist_printer.c
void	print_list(t_list *list);
void	export_print(t_list *list);
void	print_env_node(t_node *node);
void	print_export_node(t_node *node);

#endif
