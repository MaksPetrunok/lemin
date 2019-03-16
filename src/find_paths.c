/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 20:31:16 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/14 21:08:39 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"


static void			make_path(t_node *n)
{
	int	dist;

ft_printf("END: %s\n", g_farm.end->id);
	dist = 1;
	g_farm.end->in_path = 1;
	g_farm.end->dist = dist++;
	while (n != g_farm.start)
	{
ft_printf("N> : %s	Dist to end: %d, PathID: %d\n", n->id, dist, g_farm.path_id);
		n->in_path = g_farm.path_id;
		n->dist = dist++;
		n = n->in->node;
	}
	g_farm.path_id++;
	if (n != g_farm.start)
		ft_printf("START NOT REACHED!\n");
	else
ft_printf("START: %s\n", g_farm.start->id);
}



// if path from node 'n' to node 'end' found - return 1, otherwise return 0
int	find_paths(t_node *n)
{
	t_queue		*queue;
	t_adj_lst	*tmp;
	int			path_found;


	path_found = 0;
	n->dist = 0;
	refresh_graph(g_farm.start);
	queue = init_queue(n);
	while (queue->lst) // && has_unvisited(start) && has_unvisited(end))
	{
ft_printf("queue=%s\n", queue->lst->node->id);
		tmp = queue->lst->node->out;
		while (tmp)
		{
			if (tmp->node == g_farm.end)
			{
				make_path(queue->lst->node);
				path_found++;
			}
			else
				queue_add(tmp->node, queue->lst->node, queue);
			tmp = tmp->next;
		}
		queue_next(queue);
	}
	free_queue(queue);
	return (path_found);
}
