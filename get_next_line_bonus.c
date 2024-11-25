/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:36:15 by chdonnat          #+#    #+#             */
/*   Updated: 2024/11/25 15:00:18 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_add_to_list(t_list **p_list, char *buff, int readed)
{
	int		i;
	t_list	*last;
	t_list	*new_node;

	new_node = (t_list *) malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->content = (char *) malloc(readed + 1);
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (buff[i] && i < readed)
	{
		new_node->content[i] = buff[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*p_list == 0)
	{
		*p_list = new_node;
		return ;
	}
	last = ft_lst_get_last(*p_list);
	last->next = new_node;
}

void	ft_read_to_list(int fd, t_list **p_list)
{
	char	*buff;
	int		readed;

	readed = 1;
	while (ft_has_newline(*p_list) == 0 && readed != 0)
	{
		buff = (char *) malloc(BUFFER_SIZE + 1);
		if (buff == 0)
			return ;
		readed = (int) read(fd, buff, BUFFER_SIZE);
		if (readed == -1)
		{
			free(buff);
			return (free(*p_list));
		}
		if ((*p_list == 0 && readed == 0))
			return (free(buff));
		buff[readed] = '\0';
		ft_add_to_list(p_list, buff, readed);
		free (buff);
	}
}

void	ft_generate_line(char **p_line, t_list *list)
{
	int	i;
	int	len;

	len = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		list = list->next;
	}
	*p_line = (char *) malloc(len + 1);
}

void	ft_extract_line(t_list *list, char **p_line)
{
	int	i;
	int	j;

	if (!list)
		return ;
	ft_generate_line(p_line, list);
	if (*p_line == 0)
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				(*p_line)[j++] = list->content[i];
				break ;
			}
			(*p_line)[j++] = list->content[i++];
		}
		list = list->next;
	}
	(*p_line)[j] = '\0';
}

char	*get_next_line(int fd)
{
	static t_list	*list[1024];
	char			*line[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line[fd] = NULL;
	ft_read_to_list(fd, &list[fd]);
	if (!list[fd])
		return (NULL);
	ft_extract_line(list[fd], &line[fd]);
	ft_clean_list(&list[fd]);
	if (line[fd][0] == '\0')
	{
		ft_free_list(list[fd]);
		list[fd] = NULL;
		free(line[fd]);
		return (NULL);
	}
	return (line[fd]);
}
/*
#include <stdio.h>
int main(void)
{
	int		fd[1024];
	char	*line[1024];


	fd[1] = open("test", O_RDONLY);
	while((line = get_next_line(fd[1])) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd[1]);
	fd[2] = open("test2", O_RDONLY);
	while((line = get_next_line(fd[2])) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd[2]);
	
	fd[1] = open("test", O_RDONLY);
	fd[2] = open("test2", O_RDONLY);
	while((line[1] = get_next_line(fd[1])) != NULL && \
			(line[2] = get_next_line(fd[2])) != NULL)
	{
		printf("%s", line[1]);
		free(line[1]);
		printf("%s", line[2]);
		free(line[2]);
	}
	close(fd[1]);
	close(fd[2]);
	return (0);
}
*/
