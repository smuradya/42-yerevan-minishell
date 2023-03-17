/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new_elem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhakob2 <anhakob2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:58:12 by anhakob2          #+#    #+#             */
/*   Updated: 2023/01/21 19:50:29 by anhakob2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
	}
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*str;
	long		len;
	long int	num;

	num = n;
	len = ft_len(num);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	if (num < 0)
		num *= -1;
	if (num == 0)
		str[0] = 48;
	str[len--] = '\0';
	while (num > 0)
	{
		str[len] = num % 10 + '0';
		num = num / 10;
		len--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

void	*ft_memset(void *src, int c, size_t len)
{
	size_t	i;
	char	*dest;

	dest = src;
	i = 0;
	while (i < len)
	{
		*(dest + i) = (char)c;
		i++;
	}
	return (src);
}

static size_t	ft_slen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		i;
	int		j;

	join = (char *)malloc(ft_slen(s1) + ft_slen(s2) + 1);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		join[j] = s1[i];
		j++;
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		join[j] = s2[i];
		j++;
		i++;
	}
	join[j] = '\0';
	return (join);
}
