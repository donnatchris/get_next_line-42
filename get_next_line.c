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

static char	*ft_strdup(const char *s)
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

static char	*ft_initialize_line(char **backup)
{
	char	*line;

	if (!*backup)
	{
		*backup = malloc(1);
		if (!*backup)
			return (NULL);
		(*backup)[0] = '\0';
	}
	line = ft_strdup(*backup);
	if (!line)
		return (NULL);
	free(*backup);
	*backup = NULL;
	return (line);
}

static char	*ft_handle_read(char **line, char *buff, \
	size_t bytes_read, char **backup)
{
	size_t	eol_pos;
	char	*temp_line;

	eol_pos = ft_eol_search(buff, bytes_read);
	temp_line = *line;
	if (eol_pos < bytes_read)
	{
		*line = ft_strjoin(temp_line, ft_strlen(temp_line), buff, eol_pos + 1);
		if (!line)
			return (NULL);
		*backup = ft_substr(buff, eol_pos + 1, bytes_read - eol_pos - 1);
		if (!backup)
			return (NULL);
	}
	else
	{
		*line = ft_strjoin(temp_line, ft_strlen(temp_line), buff, bytes_read);
		if (!*line)
			return (NULL);
	}
	return (free(temp_line), *line);
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*line;
	size_t		bytes_read;
	static char	*backup = NULL;

	line = ft_initialize_line(&backup);
	if (!line)
		return (NULL);
	buff = malloc(BUFFER_SIZE);
	if (!buff)
		return (free(line), NULL);
	while (1)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buff);
			if (bytes_read == 0 && line[0] != '\0')
				return (line);
			free (line);
			return (NULL);
		}
		if (!ft_handle_read(&line, buff, bytes_read, &backup))
			break ;
		if (backup)
			break ;
	}
	return (free(buff), line);
}

# include <stdio.h>
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file_to_read", O_RDONLY);
	if (fd == -1)
	{
		write(2, "Open file error\n", 16);
		return (1);
	}
	while (line != NULL)
	{
		line = get_next_line(fd);
		printf("%s", line);
		sleep(1);
	}
	return (0);
}

