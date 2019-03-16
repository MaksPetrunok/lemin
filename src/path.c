/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 20:31:16 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/14 21:08:39 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
static void			make_path(t_node *n)
{
	int	dist;

ft_printf("END: %s\n", g_farm.end->id);
	dist = 1;
	g_farm.end->in_path = 1;
	g_farm.end->dist = dist++;
	while (n->in_path == 0 && n != g_farm.start)
	{
ft_printf("N> : %s	Dist to end: %d, PathID: %d\n", n->id, dist, g_farm.path_id);
		n->in_path = g_farm.path_id;
		n->dist = dist++;
		n = n->prev;
	}
	g_farm.path_id++;
	if (n != g_farm.start)
		ft_printf("START NOT REACHED!\n");
	else
ft_printf("START: %s\n", g_farm.start->id);
}
*/

void	refresh_graph(t_node *n)
{
	t_adj_lst	*lst;

	n->visit = 0;
	lst = n->adj;
	while (lst)
	{
		if (lst->node->visit)
			refresh_graph(lst->node);
		lst = lst->next;
	}
	lst = n->out;
	while (lst)
	{
		if (lst->node->visit)
			refresh_graph(lst->node);
		lst = lst->next;
	}
}

void	remove_dead_end(t_node *n)
{
	t_node		*adjacent;
	t_adj_lst	*lst;

	if (n == g_farm.start || n == g_farm.end)
		return ;
	adjacent = n->adj->node;
	lst = adjacent->adj;
	while (lst && lst->node != n)
		lst = lst->next;
	if (lst)
		remove_link(adjacent, lst);
}

void	cleanup(t_node *n)
{
	t_adj_lst	*lst;
	t_node		*adjacent;
	t_adj_lst	*next;

	lst = n->adj;
	while (lst)
	{
		next = lst->next;
		adjacent = lst->node;
		if (adjacent->dist == n->dist)
			remove_link(n, lst);
		if (adjacent->dist > n->dist && adjacent != g_farm.end)
			cleanup(adjacent);
		lst = next;
	}
	if (n != g_farm.start && n != g_farm.end &&
		n->adj && n->adj->next == NULL) // only 1 link - dead end
	{
//		ft_printf("DEAD END: %s at %s\n", n->id, n->adj->node->id);
		remove_dead_end(n);
	}
}

// if path from node 'n' to node 'end' found - return 1, otherwise return 0
int	bfs(t_node *n)
{
	t_queue		*queue;
	t_adj_lst	*tmp;
	int			path_found;

	path_found = 0;
	n->dist = 0;
	queue = init_queue(n);
	while (queue->lst) // && has_unvisited(start) && has_unvisited(end))
	{
		tmp = queue->lst->node->adj;
		while (tmp)
		{
			if (tmp->node == g_farm.end)
				path_found = 1;
			else
				queue_add(tmp->node, queue->lst->node, queue);
			tmp = tmp->next;
		}
		queue_next(queue);
	}
	free_queue(queue);
	cleanup(g_farm.start);
	refresh_graph(g_farm.start);
	return (path_found);
}
