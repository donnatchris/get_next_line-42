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

typedef struct	s_raw
{
	char	*str;
	size_t	len;
}				t_raw;

char	*ft_strndup(const char *s, size_t len)
{
	size_t		i;
	char		*dup;

	dup = (char *) malloc (sizeof(*dup) * (len + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	*ft_calloc(size_t nmemb, size_t size)
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
	return ((void *) new);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	char			*d;
	const char		*s;

	if (!dst && !src)
		return (NULL);
	d = (char *) dst;
	s = (const char *) src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	if (d > s)
	{
		while (n > 0)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
		return (dest);
	}
	return (ft_memcpy(dest, src, n));
}

size_t	ft_read(int fd, char **buff, char **line, t_raw *remainder)
{
	size_t	n_read;
	size_t	eol_i;
	char	*temp;

	while (1)
	{
		// lecture du fichier
		n_read = read(fd, *buff, BUFFER_SIZE);
		if (n_read == 0)
			return (0);
		// recherche de eol dans buff
		eol_i = ft_eol_search(*buff, n_read);
		// si eol dans buff
		if (eol_i < n_read)
		{
			temp = ft_strndup(*line, ft_strlen(*line));
			if (!temp)
				return (0);
			free(*line);
			*line = ft_strjoin(temp, ft_strlen(temp), *buff, eol_i);
			free(temp);
			if (!line)
				return (free(temp), 0);
			if (remainder->str == NULL)
			{
				remainder->str = ft_calloc(BUFFER_SIZE, 1);
				if (!remainder->str)
					return (0);
			}
			remainder->len = n_read - (eol_i + 1); 
			remainder->str = ft_memcpy(remainder->str, &(*buff)[eol_i + 1], remainder->len);
			return (n_read);
		}
		// si eol pas dans buff
		temp = ft_strndup(*line, ft_strlen(*line));
		if (!temp)
			return (0);
		free(*line);
		*line = ft_strjoin(temp, ft_strlen(temp), *buff, n_read);
		free(temp);
		if (!*line)
			return (free(temp), 0);
	}
}

char	*ft_line(int fd, char **buff, t_raw *remainder)
{
	size_t	n_read;
	char	*line;
	size_t	eol_i;

	// si remainder n est pas vide
	if (remainder->str && remainder->len)
	{
		//  recherche de eol dans remainder
		eol_i = ft_eol_search(remainder->str, remainder->len);
		// si eol dans remainder on copie le morceau, coupe remainder et on envoie line
		if (eol_i < remainder->len)
		{
			line = ft_strndup(remainder->str, eol_i + 1);
			if (!line)
				return (free(remainder->str), NULL);
			remainder->str = ft_memmove(remainder->str, &remainder->str[eol_i + 1], remainder->len - (eol_i + 1));
			remainder->len = remainder->len - (eol_i - 1);
			return (line);
		}
		// si pas de eol dans remainder on copie tout remainder dans line
		line = ft_strndup(remainder->str, remainder->len);
		if (!line)
			return (free(remainder->str), NULL);
	}
	n_read = ft_read(fd, buff, &line, remainder);
	if (n_read == 0)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	char			*line;
	char			*buff;
	static t_raw	remainder;

// verification de validite
	if (fd == -1)
		return (NULL);
// initialisation de buff
	buff = ft_calloc(BUFFER_SIZE, 1);
	if (!buff)
		return (NULL);
// si c est le premier appel ou si backup est vide
	
	if (remainder.str == NULL)
	{
		remainder.str = ft_calloc(BUFFER_SIZE, 1);
		if (remainder.str == NULL)
			return (free(buff), NULL);
		remainder.len = 0;
	}
// remplir la ligne
	line = ft_line(fd, &buff, &remainder);
// retourner la ligne et vider buff et remainder si necessaire
	if (remainder.len == 0)
	{
		free(remainder.str);
		remainder.str = NULL;
	}
	return (free(buff), line);
}

#include <stdio.h>
int	main(void)
{
	int		fd;
	char	*line = NULL;

	fd = open("file_to_read", O_RDONLY);
	if (fd == -1)
	{
		write(2, "Open file error\n", 16);
		return (1);
	}
	line = get_next_line(fd);
	printf("%s", line);
/*	while (line)
	{
		printf("%s", line);
		sleep(1);
		free(line);
		line = get_next_line(fd);
	}
*/
	return (0);
}

