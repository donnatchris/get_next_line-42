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
# include <stdio.h>

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while(str[len])
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

char	*get_next_line(int fd)
{
	char		*buff;
	char		*line;
	char		*temp_line;
	size_t		bytes_read;
	size_t		eol_pos;
	int 		eol;
	static char	*backup = NULL;

	eol = 0;
	if (backup == NULL)
	{
		backup = (char *) malloc(1);
		if (backup == NULL)
			return (NULL);
		backup[0] = '\0';
	}
	line = backup;
	buff  = (char *) malloc(BUFFER_SIZE);
	if (!buff)
	{
		free(line);
		return (NULL);
	}
	while (!eol)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buff);
			if (line[0] == '\0')
			{
				free(line);
				return (NULL);
			}
			return (line);
		}
		eol_pos = ft_eol_search(buff, bytes_read);
		temp_line = line;
		if (eol_pos < bytes_read)
		{
			eol = 1;
			line = ft_strjoin(temp_line, ft_strlen(temp_line), buff, eol_pos + 1);
			backup = ft_substr(buff, eol_pos, BUFFER_SIZE - eol_pos);
		}
		else
		{
			line = ft_strjoin(temp_line, ft_strlen(temp_line), buff, bytes_read);
		}
	}
	free(temp_line);
	if (!line)
	{
		free(buff);
		return (NULL);
	}
	free (buff);
	return (line);
}

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
/*
LA FONCTION READ

ssize_t read(int fd, void *buf, size_t count);

fd : Un descripteur de fichier.
Il représente le fichier ou la source de données à partir de laquelle on souhaite lire.
Il est généralement obtenu via un appel à open().
Cela peut aussi être un descripteur spécial comme STDIN_FILENO pour l'entrée standard>

buf : Un pointeur vers un buffer où les données lues seront stockées.
C'est une zone mémoire où read() mettra les octets qu'il a lus.

count : Le nombre maximum d'octets à lire.
C'est la taille du buffer buf, et le nombre d'octets que vous souhaitez tenter de lire.
*/
