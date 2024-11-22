#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_found_newline(t_list *stash)
{
	int		i;
	t_list	*current;

	if (!stash)
		return (0);
	current = ft_lst_get_last(stash);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_free_stash(t_list *stash)
{
	t_list	*current;
	t_list	*next;

	current = stash;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}

t_list	*ft_lst_get_last(t_list *stash)
{
	t_list	*current;

	current = stash;
	while(current && current->next)
		current = current->next;
	return (current);
}

void	ft_clean_stash(t_list	**p_stash)
{
	t_list	*last;
	t_list	*clean_node;
	int i;
	int	j;

	clean_node = (t_list *) malloc(sizeof(t_list));
	if (!(*p_stash) || !clean_node)
		return ;
	clean_node->next = NULL;
	last = ft_lst_get_last(*p_stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = (char *) malloc((ft_strlen(last->content) - i) + 1);
	if (!(clean_node->content))
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	ft_free_stash(*p_stash);
	*p_stash = clean_node;
}
