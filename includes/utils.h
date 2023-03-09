/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:38:06 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/05 14:49:05 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

// utils1.c

long double	ft_atoi(const char *str);
void		ft_putnbr_fd(int n, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *str, int fd);
char		*ft_strchr(const char *s, int c);

// utils2.c
char		*ft_strdup(const char *s1);
int			ft_strlen(const char *str);
int			ft_strcmp(char *s1, char *s2);
void		ft_putstr_fd(char *str, int fd);
char		**ft_split(char const *s, char c);

// utils3.c
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*extra_strjoin(char const *s1, char const *s2, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);

//utils4.c
char		*ft_itoa(int n);
void		ft_bzero(void *s, size_t n);
void		*ft_memset(void *src, int c, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);

// utils5.c
void		*ft_calloc(size_t count, size_t size);

// free.c
void		free_array(char **text);

// UTILS_H
int			ft_tolower(int c);

//char	*ft_strjoin(char const *s1, char const *s2);
char		**ft_split_whit(char *str);
int			ft_strlen(const char *result);
void		ft_putendl_fd(char *str, int fd);

#endif 