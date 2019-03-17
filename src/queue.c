/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 20:31:16 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/14 21:08:39 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	queue_next(t_queue *queue)
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

void	free_queue(t_queue *q)
{
	if (q == NULL)
		return ;
	while (q->lst)
		queue_next(q);
	free((void *)q);
}

/*
// node=from, adj=to
static int			add_direct_link(t_node *node, t_node *adj)
{
	t_adj_lst	*link_1;
	t_adj_lst	*link_2;

	if ((link_1 = malloc(sizeof(t_adj_lst))) == NULL ||
		(link_2 = malloc(sizeof(t_adj_lst))) == NULL)
	{
		perror("lem-in: ");
		exit(1);
	}
	link_1->node = adj;
	link_1->next = node->out;
	node->out = link_1;
	link_2->node = node;
	link_2->next = adj->in;
	adj->in = link_2;
	return (1);
}

static int		link_exists(t_node *n1, t_node *n2)
{
	t_adj_lst	*lst;

	lst = n1->in;
	while (lst)
	{
		if (lst->node == n2)
			return (1);
		lst = lst->next;
	}
	lst = n1->out;
	while (lst)
	{
		if (lst->node == n2)
			return (1);
		lst = lst->next;
	}
	return (0);
}
*/
void	queue_add(t_node *node, t_node *prev, t_queue *queue)
{
	t_adj_lst	*new;

//	if (node != g_farm.start && !link_exists(node, prev) && prev != g_farm.end)
//		add_direct_link(prev, node); // prevent adding direct links over existing direct links
	if (node->visit || node->in_path)
		return ;
	if ((new = malloc(sizeof(t_adj_lst))) == NULL)
	{
		perror("lem-in: ");
		exit(1);
	}
	node->prev = prev;
	node->visit = 1;
	if (node != g_farm.start && node != g_farm.end)
		node->dist = MIN((prev->dist + 1), node->dist);
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
