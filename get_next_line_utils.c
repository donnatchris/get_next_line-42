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

size_t ft_eol_search(const char *str, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        if (str[i] == '\n')
            return (i);
    }
    return (len); // Retourne la longueur si aucun '\n' trouvé
}

char *ft_strjoin(char *s1, const char *s2, size_t len2)
{
    size_t len1 = s1 ? ft_strlen(s1) : 0;
    char *result = (char *)malloc(len1 + len2 + 1);
    if (!result)
        return (NULL);

    if (s1)
        ft_memmove(result, s1, len1);
    ft_memmove(result + len1, s2, len2);
    result[len1 + len2] = '\0';

    return (result);
}
