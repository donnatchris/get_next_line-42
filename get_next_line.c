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

size_t	ft_newline_in_buff(char **newline_pos, \
	char **buff, char **line, char **remainder)
{
	size_t	eol_index;
	char	*temp;

	eol_index = *newline_pos - *buff;
	temp = ft_strjoin(*line, *buff, eol_index + 1);
	if (!temp)
		return (0);
	ft_free(1, *line);
	*line = temp;
	ft_free(1, *remainder);
	*remainder = ft_strndup(*newline_pos + 1, ft_strlen(*newline_pos + 1));
	return (1);
}

size_t	ft_read(int fd, char **buff, char **line, char **remainder)
{
	size_t	n_read;
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
			return (ft_newline_in_buff(&newline_pos, buff, line, remainder));
		}
		temp = ft_strjoin(*line, *buff, n_read);
		if (!temp)
			return (0);
		ft_free(1, *line);
		*line = temp;
	}
}

char	*ft_return_cpy_remainder(char *line, \
	char **newline_pos, char **remainder)
{
	char	*new_remainder;

	line = ft_strndup(*remainder, *newline_pos - *remainder + 1);
	if (!line)
		return (NULL);
	new_remainder = ft_strndup(*newline_pos + 1, ft_strlen(*newline_pos + 1));
	if (!new_remainder)
		return (line);
	ft_free(1, *remainder);
	*remainder = new_remainder;
	return (line);
}

char	*ft_line(int fd, char **buff, char **remainder)
{
	char	*newline_pos;
	char	*line;

	line = NULL;
	if (*remainder)
	{
		newline_pos = ft_strchr(*remainder, '\n');
		if (newline_pos)
		{
			line = ft_return_cpy_remainder(line, &newline_pos, remainder);
			return (line);
		}
		line = ft_strndup(*remainder, ft_strlen(*remainder));
		ft_free(1, *remainder);
		*remainder = NULL;
	}
	else
		line = NULL;
	if (ft_read(fd, buff, &line, remainder) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
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
	ft_free(1, buff);
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
