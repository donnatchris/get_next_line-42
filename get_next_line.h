/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:55:34 by chdonnat          #+#    #+#             */
/*   Updated: 2024/11/15 17:13:22 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <fcntl.h>
# include <unistd.h> 
# include <stdlib.h> 

typedef struct	s_raw
{
	char	*str;
	size_t	len;
}				t_raw;

char *ft_strndup(const char *s, size_t len);
char	*ft_calloc(size_t nmemb, size_t size);
char	*ft_memmove(char *dest, const char *src, size_t n);
size_t ft_read(int fd, char **buff, char **line, char **remainder);
char *ft_line(int fd, char **buff, char **remainder);
char *get_next_line(int fd);
size_t	ft_strlen(const char *str);
size_t ft_eol_search(const char *str, size_t len);
char *ft_strjoin(char *s1, const char *s2, size_t len2);

#endif
