/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escort.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:01:15 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/14 17:39:23 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	move_ant(t_ant *ant)
{
	t_adj_lst	*lst;

	lst = ant->node->adj;
	while (lst)
	{
		// add smart conditions
		// use direct links
		if (lst->node != ant->prev_node &&
			lst->node->ant == 0 &&
			lst->node->dist <= ant->node->dist)
		{
			ft_printf("L%d-%s ", ant->id, lst->node->id);
			if (lst->node != g_farm.end)
				lst->node->ant = ant->id;
			else
				lst->node->ant = 0;
			ant->prev_node = ant->node;
			ant->node->ant = 0;
			ant->node = lst->node;
			break ;
		}
		lst = lst->next;
	}
}

static void	add_ants(t_ant_queue *q)
{
	t_adj_lst	*lst;
	int			ants_sent;

	ants_sent = 0;
	lst = g_farm.start->adj;
// ft_printf("Max ants = %d\n", MIN(g_farm.inputs, g_farm.outputs));
	while (lst && ants_sent < (MIN(g_farm.inputs, g_farm.outputs)) && 				g_farm.next_ant <= g_farm.ants_number)
	{
		// modify smart conditions ?
		if (lst->node->ant == 0 && lst->node->dist < 2000000 &&
			// (lst->node == g_farm.start->adj->node ||
			(g_farm.ants_number - g_farm.next_ant >= lst->node->dist - g_farm.start->adj->node->dist))//)
		{
			ft_printf("L%d-%s ", g_farm.next_ant, lst->node->id);
			ft_printf("[%d] ", lst->node->dist); // debug
			ant_queue_add(g_farm.next_ant, lst->node, q);
			lst->node->ant = g_farm.next_ant++;
			ants_sent++;
		}
		lst = lst->next;
	}
}

t_ant_queue	*init_ants(void)
{
	t_ant_queue	*q;

	if ((q = malloc(sizeof(t_ant_queue))) == NULL)
	{
		perror("lem-in: ");
		exit(1);
	}
	q->lst = NULL;
	q->last = NULL;
	add_ants(q);
	ft_printf("\n");
	return (q);
}

void	escort_ants(void)
{
	t_ant_queue	*queue;
	t_ant		*ant;

	ft_printf("\n");
	g_farm.next_ant = 1;
	queue = init_ants();
	while (queue->lst)
	{
		while (queue->lst && queue->lst->node == g_farm.end)
			ant_queue_next(queue);
		ant = queue->lst;
		while (ant)
		{
			move_ant(ant);
			ant = ant->next;
		}
		add_ants(queue);
		ft_printf("\n");
	}
	free((void *)queue);
}
