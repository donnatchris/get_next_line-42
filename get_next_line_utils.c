/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:54:43 by chdonnat          #+#    #+#             */
/*   Updated: 2024/11/15 14:55:15 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

size_t	ft_eol_search(char *str, size_t bytes_read)
{
	size_t	pos;

	pos = 0;
	while (pos < bytes_read)
	{
		if (str[pos] == '\n')
			return (pos);
		pos++;
	}
	return (bytes_read);
}

char	*ft_strjoin(char const *s1, size_t size1, char const *s2, size_t size2)
{
	char	*join;
	size_t	size;
	size_t	i;
	size_t	j;

	size = size1 + size2;
	join = (char *) malloc((size + 1) * sizeof(char));
	if (join == NULL)
		return (NULL);
	i = 0;
	while (i < size1)
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < size2)
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}

static size_t	ft_cpy_len(char const *s, unsigned int start, size_t len)
{
	size_t	cpy_len;

	if (start + len > ft_strlen(s))
		cpy_len = ft_strlen(s) - start;
	else
		cpy_len = len;
	return (cpy_len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*cpy;
	size_t	i;
	size_t	cpy_len;

	if (start >= ft_strlen(s))
	{
		cpy = (char *) malloc(sizeof(char));
		if (cpy == NULL)
			return (NULL);
		cpy[0] = '\0';
		return (cpy);
	}
	cpy_len = ft_cpy_len(s, start, len);
	cpy = (char *) malloc((cpy_len + 1) * sizeof(char));
	if (cpy == NULL)
		return (NULL);
	i = 0;
	while (i < cpy_len)
	{
		cpy[i] = s[i + start];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
