/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 09:47:38 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/12 20:31:53 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_node		*init_node(const char *str)
{
	t_node	*node;
	char	*ptr;
	t_node	*ref;

	ptr = ft_strchr(str, ' ');
	ref = NULL;
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
		return (NULL);
	}
	node->x = ft_atoi(ptr);
	node->y = ft_atoi(ft_strchr(ptr + 1, ' '));
	node->adj = NULL;
	node->ant = 0;
	node->visited = NULL;
	node->dist = 2000000;
	return (node);
}

static int	check_link(t_node *node, t_node *adj)
{
	t_adj_lst	*link;

	if (!node || !adj)
		return (0);
	if (node == adj)
	{
		ft_dprintf(2, "lem-in: incorrect link %s-%s\n", node->id, adj->id);
		return (0);
	}
	link = node->adj;
	while (link)
	{
		if (link->node == adj)
		{
			ft_dprintf(2, "lem-in: link %s-%s already exists\n",
				node->id, link->node->id);
			return (0);
		}
		link = link->next;
	}
	return (1);
}

int			add_link(t_node *node, t_node *adj)
{
	t_adj_lst	*link;

	if (!check_link(node, adj))
		return (0);
	if ((link = malloc(sizeof(t_adj_lst))) == NULL)
	{
		perror("lem-in: ");
		return (0);
	}
	link->node = adj;
	link->next = node->adj;
	node->adj = link;
	return (1);
}

void		free_node(t_node *node)
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
