/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 20:31:16 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/14 21:08:39 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ant_queue_push(t_ant_queue *queue)
{
	t_ant	*tmp;

	if (queue == NULL || queue->lst == NULL || queue->lst->next == NULL)
		return ;
	tmp = queue->lst;
	tmp->next = NULL;
	queue->lst = queue->lst->next;
	queue->last->next = tmp;
	queue->last = tmp;
}

void	ant_queue_next(t_ant_queue *queue)
{
	t_ant	*tmp;

	if (queue == NULL || queue->lst == NULL)
		return ;
	tmp = queue->lst->next;
	free((void *)queue->lst);
	queue->lst = tmp;
	if (tmp == NULL)
		queue->last = NULL;
}

void	ant_free_queue(t_ant_queue *q)
{
	if (q == NULL)
		return ;
	while (q->lst)
		ant_queue_next(q);
	free((void *)q);
}

void	ant_queue_add(int id, t_node *node, t_ant_queue *queue)
{
	t_ant	*new;

	if ((new = malloc(sizeof(t_ant))) == NULL)
	{
		perror("lem-in: ");
		exit(1);
	}
	new->id = id;
	new->node = node;
	new->prev_node = g_farm.start;
	new->next = NULL;
	if (queue->lst == NULL)
		queue->lst = new;
	if (queue->last != NULL)
		queue->last->next = new;
	queue->last = new;
}
