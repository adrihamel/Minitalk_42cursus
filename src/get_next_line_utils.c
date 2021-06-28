/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguerrer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 18:14:39 by aguerrer          #+#    #+#             */
/*   Updated: 2021/06/28 17:47:24 by aguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strdup(char *s1)
{
	char	*p;
	char	*aux;

	p = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!p)
		return (NULL);
	aux = p;
	while (*s1)
		*aux++ = *s1++;
	*aux = '\0';
	return (p);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (0);
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (p == NULL)
		return (0);
	i = 0;
	while (*(s1 + i) != '\0')
	{
		*(p + i) = *(s1 + i);
		i++;
	}
	j = 0;
	while (*(s2 + j) != '\0')
	{
		*(p + i) = *(s2 + j);
		i++;
		j++;
	}
	*(p + i) = '\0';
	return (p);
}

char	*ft_strchr(char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == ((char)c))
			return ((char *)s);
		s++;
	}
	if (((char)c) == '\0')
		return ((char *)s);
	return (0);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*aux;
	char	*str;

	if (s == NULL)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	str = malloc(len + 1);
	if (str == NULL)
		return (0);
	aux = str;
	while ((*(s + start) != '\0') && len--)
		*aux++ = *(s++ + start);
	*aux = '\0';
	return (str);
}

int	ft_strlen(char *s)
{
	size_t	n;

	n = 0;
	while (*s != '\0')
	{
		n++;
		s++;
	}
	return (n);
}
