// header

#include "farm.h"

t_node	*init_node(const char *id, int x, int y)
{
	t_node	*node;

	if ((node = malloc(sizeof(t_node))) == NULL ||
		(node->id = ft_strdup(id)) == NULL)
	{
		if (node)
			free((void *)(node->id));
		free((void *)node);
		ft_dprintf(2,
			"memory allocation error when initializing node '%s'\n", id);
		return (NULL);
	}
	node->x = x;
	node->y = y;
	node->adj = NULL;
	return (node);
}

void	free_node(t_node *node)
{
	t_adj_lst	*tmp;

	if (node == NULL)
		return ;
	free((void *)(node->id));
	while (node->adj)
	{
		tmp = node->adj;
		node->adj = tmp->next;
		free((void *)tmp);
	}
	free((void *)node);
}
