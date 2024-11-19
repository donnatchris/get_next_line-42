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

size_t			ft_strlen(const char *str);
size_t			ft_eol_search(char *str, size_t bytes_read);
char			*ft_strjoin(char const *s1, size_t size1, \
	char const *s2, size_t size2);
static size_t	ft_cpy_len(char const *s, unsigned int start, size_t len);
char			*ft_substr(char const *s, unsigned int start, size_t len);
static char		*ft_strdup(const char *s);
static char		*ft_initialize_line(char **backup);
static char		*ft_handle_read(char **line, char *buff, \
	size_t bytes_read, char **backup);
char			*get_next_line(int fd);

#endif
