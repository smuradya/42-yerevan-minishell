
#include "utils.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	int		strl;

	if (!s1)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	strl = ft_strlen(s1);
	while (strl && ft_strchr(set, s1[strl]))
		strl--;
	new = ft_substr(s1, 0, strl + 1);
	return (new);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset (s, '\0', n);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tab;

	tab = malloc(count * size);
	if (!tab)
		return (tab);
	ft_bzero(tab, count * size);
	return (tab);
}
