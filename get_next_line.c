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

size_t	ft_strlen_gnl(const char *str)
{
	size_t	len;

	len = 0;
	while(str[len])
		len++;
	return (len);
}

static int	ft_is_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_trim_len(const char *s, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	len;

	len = ft_strlen_gnl(s);
	if (len == 0)
		return (0);
	i = 0;
	while (ft_is_set(s[i], set))
		i++;
	if (i == len)
		return (0);
	j = 0;
	while (ft_is_set(s[len - j - 1], set) && (len - j) > 0)
		j++;
	return (len - i - j);
}

char	*ft_strtrim_gnl(char const *s1, char const *set)
{
	char	*trim;
	size_t	len;
	size_t	i;
	size_t	j;

	if (s1 == NULL)
		return (NULL);
	len = ft_trim_len(s1, set);
	trim = (char *) malloc((len + 1) * sizeof(char));
	if (trim == NULL)
		return (NULL);
	i = 0;
	while (ft_is_set(s1[i], set))
		i++;
	j = 0;
	while (j < len)
	{
		trim[j] = s1[i + j];
		j++;
	}
	trim[j] = '\0';
	return (trim);
}

void	ft_strcat_gnl(char *dst, const char *src)
{
	size_t	i;
	size_t	j;

	if (!dst || !src)
		return ;
	i = 0;
	while (dst[i])
		i++;
	j = 0;
	while (src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
}

char	*ft_strdup_gnl(const char *s)
{
	size_t		i;
	char		*dup;

	dup = (char *) malloc (sizeof(*dup) * (ft_strlen_gnl(s) + 1));
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

char	*ft_realloc_gnl(char *str, size_t new_size)
{
	static char	*new_str = NULL;
	size_t		i;

	if (new_size == 0)

	{
		free(str);
		return (NULL);
	}
	new_str = (char *) malloc(new_size);
	if (new_str == NULL)
		return (NULL);
	if (str == NULL)
	{
		new_str[0] = '\0';
		return (new_str);
	}
	i = 0;
	while (str[i] && i < new_size - 1)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

size_t	ft_eol_search_gnl(char *str, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

char	*get_next_line(int fd)
{
	char			*buff;
	char			*line;
	size_t			bytes_read;
	size_t			total_bytes = 0;
	int 			eol;


	eol = 0;
	line = NULL;
	buff  = (char *) malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (eol == 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		total_bytes += bytes_read;
		buff[bytes_read] = '\0';
		line = ft_realloc_gnl(line, total_bytes + 1);
		ft_strcat_gnl(line, buff);
		printf("DANS GNL line  = %s\n", line);
		if (ft_eol_search_gnl(buff, BUFFER_SIZE) < BUFFER_SIZE || bytes_read == 0)
		{
			
			return (line);
		}
	}
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
	line = get_next_line(fd);
	printf("dane le main line est : %s\n", line);
	line = get_next_line(fd);
	printf("dane le main line est : %s\n", line);
	line = get_next_line(fd);
	printf("dane le main line est : %s\n", line);
	line = get_next_line(fd);
	printf("dane le main line est : %s\n", line);
	line = get_next_line(fd);
	printf("dane le main line est : %s\n", line);
	line = get_next_line(fd);
	printf("dane le main line est : %s\n", line);
	line = get_next_line(fd);
	printf("dane le main line est : %s\n", line);
	line = get_next_line(fd);
	printf("dane le main line est : %s\n", line);
/*
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
*/
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
