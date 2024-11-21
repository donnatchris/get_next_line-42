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
# include <stdarg.h>

void	ft_free(size_t count, ...);
size_t	ft_strlen(const char *str);
char	*ft_strndup(const char *s, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, const char *s2, size_t len2);
size_t	ft_newline_in_buff(char **newline_pos, \
	char **buff, char **line, char **remainder);
size_t	ft_read(int fd, char **buff, char **line, char **remainder);
char	*ft_return_cpy_remainder(char *line, \
	char **newline_pos, char **remainder);
char	*ft_line(int fd, char **buff, char **remainder);
char	*get_next_line(int fd);

#endif
