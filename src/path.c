/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 20:31:16 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/12 21:35:35 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_adj_lst	*last = NULL;

int		has_unvisited(t_node *node)
{
	t_adj_lst	*adj;

	while (adj)
	{
		if (adj->node->visited != NULL)
			return (1);
		adj = adj->next;
	}
	return (0);
}

static void			queue_add(t_node *node)
{
	t_adj_lst	*new;

	if ((new = malloc(sizeof(t_adj_lst))) == NULL)
	{
		perror("lem-in: ");
		exit(1);
	}
	new->node = node;
	new->next = NULL;
	if (last != NULL)
		last->next = new;
	last = new;
}

void	find_paths(t_node *start, t_node *end)
{
	t_adj_lst	*queue;
	t_adj_lst	*tmp;
	t_adj_lst	*node_adj;

	start->visited = 1;
	queue_add(start);
	while (queue) // && has_unvisited(start) && has_unvisited(end))
	{
		tmp = queue;
		while (tmp)
		{

			while (
			tmp->node->dist = 
			queue_add(tmp->node);
			tmp = tmp->next;
		}


		visit(queue->node)
	}
}
