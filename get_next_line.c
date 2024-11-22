#include "get_next_line.h"

void	ft_add_to_stash(t_list **p_stash, char *buff, int readed)
{
	int	i;
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
	if (*p_stash == 0)
	{
		*p_stash = new_node;
		return ;
	}
	last = ft_lst_get_last(*p_stash);
	last->next = new_node;
}

void	ft_read_and_stash(int fd, t_list **p_stash)
{
	char	*buff;
	int		readed;

	readed = 1;
	while (ft_found_newline(*p_stash) == 0 && readed != 0)
	{
		buff = (char *) malloc(BUFFER_SIZE + 1);
		if (buff == 0)
			return ;
		readed = (int) read(fd, buff, BUFFER_SIZE);
		if ((*p_stash == 0 && readed == 0) || readed == -1)
		{
			free (buff);
			return ;
		}
		buff[readed] = '\0';
		ft_add_to_stash(p_stash, buff, readed);
		free (buff);
	}
}

void	ft_generate_line(char **p_line, t_list *stash)
{
	int	i;
	int	len;

	len = 0;
	while(stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	*p_line = (char *) malloc(len + 1);
}

void	ft_extract_line(t_list *stash, char **p_line)
{
	int	i;
	int	j;

	if (!stash)
		return ;
	ft_generate_line(p_line, stash);
	if (*p_line == 0)
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*p_line)[j++] = stash->content[i];
				break ;
			}
			(*p_line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*p_line)[j] = '\0';
}

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	line = NULL;
	ft_read_and_stash(fd, &stash);
	if (!stash)
		return (NULL);
	ft_extract_line(stash, &line);
	ft_clean_stash(&stash);
	if (line[0] == '\0')
	{
		ft_free_stash(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

#include <stdio.h>
int main(void)
{
	int	fd;
	char	*line;

	fd = open("test", O_RDONLY);
	while((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
