/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:53:52 by chdonnat          #+#    #+#             */
/*   Updated: 2024/11/15 17:23:06 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*buff;
	size_t	bytes_read;

	buff  = (char *) malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	bytes_read = read(fd, buff, BUFFER_SIZE);
	if (bytes_read <= 0)
		{
			if (bytes_read < 0)
				write(2, "read file error\n", 16);
			free(buff);
			return (NULL);
		}
	buff[bytes_read] = '\0';
	return(buff);
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
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			printf("End of file or error\n");
		else
		{
			printf("%s", line);
			free(line);
		}
	}
	if (close(fd) != 0)
	{
		printf("Close file error\n");
		return (1);
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
