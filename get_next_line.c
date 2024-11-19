/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:53:52 by chdonnat          #+#    #+#             */
/*   Updated: 2024/11/18 13:39:26 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_strndup(const char *s, size_t len)
{
    char *dup = (char *)malloc(len + 1);
    if (!dup)
        return (NULL);
    for (size_t i = 0; i < len; i++)
        dup[i] = s[i];
    dup[len] = '\0';
    return (dup);
}

char	*ft_calloc(size_t nmemb, size_t size)
{
	char	*new;
	size_t	i;
	size_t	total_size;

	total_size = nmemb * size;
	if (total_size != nmemb * size)
		return (NULL);
	new = (char *) malloc(total_size);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		new[i] = 0;
		i++;
	}
	return (new);
}

char	*ft_memmove(char *dest, const char *src, size_t n)
{
	size_t			i;

	if (!dest && !src)
		return (NULL);
	if (dest > src)
	{
		while (n > 0)
		{
			dest[n - 1] = src[n - 1];
			n--;
		}
		return (dest);
	}
	else
	{
		i = 0;
		while (i < n)
		{
			dest[i] = src[i];
			i++;
		}
	}
	return (dest);
}

size_t ft_read(int fd, char **buff, char **line, t_raw *remainder)
{
    ssize_t n_read;
    size_t  eol_i;
    char    *temp;

    while (1)
    {
        n_read = read(fd, *buff, BUFFER_SIZE);
        if (n_read == -1)
            return (0);
        if (n_read == 0)
            return (0);
        eol_i = ft_eol_search(*buff, n_read);
        if (eol_i < (size_t)n_read)
        {
            temp = ft_strjoin(*line, *buff, eol_i + 1);
            if (!temp)
                return (0);
            free(*line);
            *line = temp;
            remainder->len = n_read - (eol_i + 1);
            free(remainder->str);
            remainder->str = ft_strndup(&(*buff)[eol_i + 1], remainder->len);
            if (!remainder->str)
                return (0);
            return (1);
        }
        temp = ft_strjoin(*line, *buff, n_read);
        if (!temp)
            return (0);
        free(*line);
        *line = temp;
    }
}

char *ft_line(int fd, char **buff, t_raw *remainder)
{
    size_t  eol_i;
    char    *line = NULL;

    if (remainder->str && remainder->len > 0)
    {
        eol_i = ft_eol_search(remainder->str, remainder->len);
        if (eol_i < remainder->len)
        {
            line = ft_strndup(remainder->str, eol_i + 1);
            if (!line)
                return (NULL);
            if (eol_i + 1 < remainder->len)
            {
                remainder->len -= (eol_i + 1);
                ft_memmove(remainder->str, &remainder->str[eol_i + 1], remainder->len);
            }
            else
            {
                free(remainder->str);
                remainder->str = NULL;
                remainder->len = 0;
            }
            return (line);
        }
        line = ft_strndup(remainder->str, remainder->len);
        if (!line)
            return (NULL);
        free(remainder->str);
        remainder->str = NULL;
        remainder->len = 0;
    }
    if (ft_read(fd, buff, &line, remainder) == 0)
    {
        return (free(line), NULL);
    }
    return (line);
}

char *get_next_line(int fd)
{
    char *line;
    char *buff;
    static t_raw remainder;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    buff = ft_calloc(BUFFER_SIZE, 1);
    if (!buff)
        return (NULL);

    if (!remainder.str)
    {
        remainder.str = ft_calloc(BUFFER_SIZE, 1);
        if (!remainder.str)
        {
            free(buff);
            return (NULL);
        }
        remainder.len = 0;
    }

    line = ft_line(fd, &buff, &remainder);

    free(buff);
    if (remainder.len == 0)
    {
        free(remainder.str);
        remainder.str = NULL;
    }

    return (line);
}

#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file_to_read", O_RDONLY);
    if (fd == -1)
    {
        perror("Open file error");
        return (1);
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
		sleep(1);
        free(line);
    }
    if (close(fd) == -1)
    {
        perror("Close file error");
        return (1);
    }
    return (0);
}

