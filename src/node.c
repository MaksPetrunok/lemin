// header

#include "lemin.h"

t_node	*init_node(const char *str)
{
	t_node	*node;
	char	*ptr;
	t_node	*ref;

	ptr = ft_strchr(str, ' ');
	if ((node = malloc(sizeof(t_node))) == NULL ||
		(node->id = ft_substr(str, ptr)) == NULL ||
		(ref = hmap_get(node->id, g_farm.map)) != NULL)
	{
		if (ref != NULL)
			ft_dprintf(2,
				"lem-in: duplicate room identifier found: %s\n", node->id);
		else
			ft_dprintf(2,
				"memory allocation error when initializing node '%s'\n", str);
		if (node)
			free((void *)(node->id));
		free((void *)node);
		return (NULL);
	}
// ---- needed only for bonuses ----
	node->x = ft_atoi(ptr);
	node->y = ft_atoi(ft_strchr(ptr + 1, ' '));
// ---------------------------------
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
