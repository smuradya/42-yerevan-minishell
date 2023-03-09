/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:09:10 by smuradya          #+#    #+#             */
/*   Updated: 2023/03/05 15:12:01 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	word_counter_new(char *str)
{
	int	i;
	int	len;

	i = -1;
	len = 1;
	while (str[++i] && (str[i] == '='))
		;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if ((str[i] == '=') && str[i + 1] > 32)
			len++;
		i++;
	}
	return (len);
}

int	word_len_counter_new(char *str)
{
	int	len;

	len = -1;
	while (str[++len] && (str[len] != '='))
		;
	return (len);
}

void	fill_word_new(char *copy_to, char *copy_from)
{
	int	len;

	len = -1;
	while (copy_from[++len]
		&& (copy_from[len] != '='))
		copy_to[len] = copy_from[len];
	copy_to[len] = '\0';
}

char	**ft_split_whit(char *str)
{
	int		i;
	int		counter;
	int		word_count;
	int		word_len;
	char	**result;

	i = -1;
	counter = -1;
	word_count = word_counter_new(str);
	result = malloc(sizeof(char *) * (word_count + 1));
	while (++counter < word_count)
	{
		while (str[++i] && (str[i] == '='))
			;
		word_len = word_len_counter_new(str + i);
		result[counter] = malloc(word_len + 1);
		fill_word_new(result[counter], str + i);
		i += word_len;
	}
	result[word_count] = 0;
	return (result);
}

char	*extra_strjoin(char const *s1, char const *s2, char c)
{
	char			*newstr;
	size_t			i;
	size_t			j;

	newstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 2);
	if (!newstr)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	newstr[i] = c;
	j = 0;
	while (s2[j] != '\0')
	{
		newstr[i + 1 + j] = s2[j];
		j++;
	}
	newstr[i + j + 1] = '\0';
	return (newstr);
}

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	else
		return (c);
}
