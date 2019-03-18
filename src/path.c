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
		// if (adjacent->dist == n->dist)
		// 	remove_link(n, lst);
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

int	count_inputs(void)
{
	t_adj_lst	*lst;
	int			count;

	count = 0;
	lst = g_farm.end->adj;
	while (lst)
	{
		if (lst->node->dist < 2000000)
			count++;
		lst = lst->next;
	}
	return (count);
}

// if path from node 'n' to node 'end' found - return 1, otherwise return 0
int	count_paths(t_node *n, t_node *dst)
{
	t_queue		*queue;
	t_adj_lst	*tmp;
	int			path_found;

	path_found = 0;
	n->dist = 0;
	queue = init_queue(n);
	while (queue->lst)
	{
		tmp = queue->lst->node->adj;
		while (tmp)
		{
			if (tmp->node == dst)
				path_found++;
			else
				queue_add(tmp->node, queue->lst->node, queue);
			tmp = tmp->next;
		}
		queue_next(queue);
	}
	free_queue(queue);
	cleanup(n);
	refresh_graph(n);
	return (path_found);
}
