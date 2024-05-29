/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:33:43 by wweerasi          #+#    #+#             */
/*   Updated: 2024/05/28 15:24:05 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	len;

	len = ft_strlen(s1);
	s2 = malloc(sizeof(char) * (len + 1));
	if (s2 != NULL)
	{
		while (*s1 != '\0')
		{
			*s2++ = *s1++;
		}
		*s2 = '\0';
		s2 -= len;
	}
	return (s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2);
	new_s = malloc((len + 1) * sizeof(char));
	if (new_s != NULL)
	{
		while (*s1 != '\0')
			*new_s++ = *s1++;
		while (*s2 != '\0')
			*new_s++ = *s2++;
		*new_s = '\0';
		new_s -= len;
	}
	return (new_s);
}

char	*ft_strchr(const char *s, int c)
{
	while (1)
	{
		if (*s == (char) c)
			return ((char *) s);
		else if (*s == '\0')
			break ;
		s++;
	}
	return (0);
}


size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++ != '\0')
		len++;
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;

	if (!s)
		return (NULL);
	else if (start > ft_strlen(s))
		return (ft_strdup(""));
	else if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub_s = malloc((len + 1) * sizeof(char));
	if (sub_s != NULL)
	{
		s += start;
		start = len;
		while (len--)
			*sub_s++ = *s++;
		*sub_s = '\0';
		sub_s -= start;
	}
	return (sub_s);
}
