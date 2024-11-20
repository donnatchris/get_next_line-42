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

char	*ft_strdup(const char *s)
{
	size_t		i;
	char		*dup;

	dup = (char *) malloc (sizeof(*dup) * (ft_strlen(s) + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	size_t			len;
	unsigned char	uc;

	len = ft_strlen(s);
	uc = (unsigned char) c;
	i = 0;
	while (i <= len)
	{
		if ((unsigned char) s[i] == uc)
			return ((char *) &s[i]);
		i++;
	}
	return (NULL);
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

size_t ft_read(int fd, char **buff, char **line, char **remainder)
{
    ssize_t	n_read;
    char	*temp;
    char	*newline_pos;

    while (1)
    {
        n_read = read(fd, *buff, BUFFER_SIZE);
        if (n_read <= 0)
            return (0);
        (*buff)[n_read] = '\0';
        newline_pos = ft_strchr(*buff, '\n');
        if (newline_pos)
        {
            size_t eol_index = newline_pos - *buff;
            temp = ft_strjoin(*line, *buff, eol_index + 1);
            if (!temp)
                return (0);
            free(*line);
            *line = temp;
            free(*remainder);
            *remainder = ft_strdup(newline_pos + 1);
            return (1);
        }
        temp = ft_strjoin(*line, *buff, n_read);
        if (!temp)
            return (0);
        free(*line);
        *line = temp;
    }
}

char *ft_line(int fd, char **buff, char **remainder)
{
    char	*newline_pos;
    char	*line;

    if (*remainder)
        newline_pos = ft_strchr(*remainder, '\n');
        if (newline_pos)
        {
            line = ft_strndup(*remainder, newline_pos - *remainder + 1);
            char *new_remainder = ft_strdup(newline_pos + 1);
            free(*remainder);
            *remainder = new_remainder;
            return (line);
        }
        line = ft_strdup(*remainder);
        free(*remainder);
        *remainder = NULL;
    }
    else
    {
        line = NULL;
    }
    if (ft_read(fd, buff, &line, remainder) == 0)
    {
        free(line);
        return (NULL);
    }
    return (line);
}

char *get_next_line(int fd)
{
    char		*line;
    char		*buff;
    static char	*remainder = NULL;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buff = (char *)malloc(BUFFER_SIZE + 1);
    if (!buff)
        return (NULL);
    line = ft_line(fd, &buff, &remainder);
    free(buff);
    return (line);
}

/*
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
*/
