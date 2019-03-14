/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 20:31:16 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/14 16:19:48 by mpetruno         ###   ########.fr       */
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

static void	queue_next(t_queue *queue)
{
	t_adj_lst	*tmp;

	if (queue == NULL || queue->lst == NULL)
		return ;
	tmp = queue->lst->next;
	free((void *)queue->lst);
	queue->lst = tmp;
	if (tmp == NULL)
		queue->last = NULL;
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
ft_printf("N> : %s	Distance to end: %d\n", n->id, dist);
		n->in_path = 1;
		n->dist = dist++;
		n = n->prev;
	}
	if (n != g_farm.start)
		ft_printf("START NOT REACHED!\n");
	else
ft_printf("START: %s\n", g_farm.start->id);
ft_printf("Path Length: %d\n", g_farm.start->id);
}

static void			free_queue(t_queue *q)
{
	if (q == NULL)
		return ;
	while (q->lst)
		queue_next(q);
	free((void *)q);
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
//ft_printf("Reset node: %s\n", n->id);
}

static void			queue_add(t_node *node, t_node *prev, t_queue *queue)
{
	t_adj_lst	*new;

	if (node->visit || node->in_path)
		return ;
	if ((new = malloc(sizeof(t_adj_lst))) == NULL)
	{
		perror("lem-in: ");
		exit(1);
	}
	node->prev = prev;
	node->visit = 1;
	new->node = node;
	new->next = NULL;
	if (queue->lst == NULL)
		queue->lst = new;
	if (queue->last != NULL)
		queue->last->next = new;
	queue->last = new;
}

t_queue	*init_queue(t_node *node)
{
	t_queue	*q;

	if ((q = malloc(sizeof(t_queue))) == NULL)
	{
		perror("lem-in: ");
		exit(1);
	}
	q->lst = NULL;
	q->last = NULL;
	queue_add(node, NULL, q);
	return (q);
}

// if path from node 'n' to node 'end' found - return 1, otherwise return 0
int	bfs(t_node *n)
{
	t_queue	*queue;
	t_adj_lst	*tmp;

	queue = init_queue(n);
	while (queue->lst) // && has_unvisited(start) && has_unvisited(end))
	{
//ft_printf("Queue: %s:\n", queue->lst->node->id);
		tmp = queue->lst->node->adj;
		while (tmp)
		{
//ft_printf("  adj: %s:\n", tmp->node->id);
			if (tmp->node == g_farm.end)
			{
				make_path(queue->lst->node);
				free_queue(queue);
				refresh_graph(g_farm.start);
				return (1);
			}
			queue_add(tmp->node, queue->lst->node, queue);
			tmp = tmp->next;
		}
		queue_next(queue);
	}
	free_queue(queue);
	return (0);
}
