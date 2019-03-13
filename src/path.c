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

/*
int		has_unvisited(t_node *node)
{
	t_adj_lst	*adj;

	while (adj)
	{
		if (adj->node->visit != 0)
			return (1);
		adj = adj->next;
	}
	return (0);
}
*/

static void			queue_add(t_node *node, t_adj_lst **queue)
{
	t_adj_lst	*new;

	if (node->visit || node->in_path)
		return ;
	node->visit = 1;
	if ((new = malloc(sizeof(t_adj_lst))) == NULL)
	{
		perror("lem-in: ");
		exit(1);
	}
	new->node = node;
	new->next = *queue;
	*queue = new;
}

static t_adj_lst	*queue_next(t_adj_lst *queue)
{
	t_adj_lst	*tmp;

	if (queue == NULL)
		return (NULL);
	tmp = queue->next;
	free((void *)queue);
	return (tmp);
}

static void			make_path(t_node *n)
{
	int	dist;

ft_printf("END: %s\n", g_farm.end->id);
	dist = 1;
	g_farm.end->in_path = 1;
	g_farm.end->dist = dist++;
	while (n->in_path == 0 && n != g_farm.start)
	{
ft_printf("N> : %s\n", n->id);
		n->in_path = 1;
		n->dist = dist++;
		n = n->prev;
	}
ft_printf("START: %s\n", g_farm.start->id);
}

static void			free_queues(t_adj_lst *q1, t_adj_lst *q2)
{
	while (q1)
		q1 = queue_next(q1);
	while (q2)
		q2 = queue_next(q2);
}

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
ft_printf("Reset node: %s\n", n->id);
}

// if path from node 'n' to node 'end' found - return 1, otherwise return 0
int	bfs(t_node *n)
{
	t_adj_lst	*queue;
	t_adj_lst	*queue_tmp;
	t_adj_lst	*tmp;

	queue = NULL;
	queue_add(n, &queue);
	while (queue) // && has_unvisited(start) && has_unvisited(end))
	{
		tmp = queue->node->adj;
		queue_tmp = NULL;
		while (tmp)
		{
			if (tmp->node == g_farm.end)
			{
				make_path(queue->node);
				free_queues(queue, queue_tmp);
				refresh_graph(g_farm.start);
				return (1);
			}
			tmp->node->prev = queue->node;
			queue_add(tmp->node, &queue_tmp);
			tmp = tmp->next;
		}
		queue = queue_next(queue);
		queue = (queue == NULL) ? queue_tmp : queue;
	}
	return (0);
}
