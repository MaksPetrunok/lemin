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

static int	g_min_dist = 999999;

static void	sort_paths(void)
{
	t_adj_lst	*head;
	t_adj_lst	*tmp;
	t_adj_lst	*iter;

	head = NULL;
	while (g_farm.start->out != NULL)
	{
		tmp = g_farm.start->out;
		g_min_dist =
			(tmp->node->dist < g_min_dist) ? tmp->node->dist : g_min_dist;
		g_farm.start->out = g_farm.start->out->next;
		if (!head || tmp->node->dist < head->node->dist)
		{
			tmp->next = head;
			head = tmp;
			continue ;
		}
		iter = head;
		while (iter->next && tmp->node->dist > iter->next->node->dist)
			iter = iter->next;
		tmp->next = iter->next;
		iter->next = tmp;
	}
	g_farm.start->out = head;
}

static int	move(t_node *from, t_node *to)
{
	int	ret;

	ret = 0;
	if (from == g_farm.start)
		return (0);
	if (from->ant != 0)
	{
		ft_printf("L%d-%s ", from->ant, to->id);
		to->ant = from->ant;
		from->ant = 0;
		ret++;
	}
	ret += move(from->prev, from);
	return (ret);
}

static int	pull_ants(void)
{
	t_adj_lst	*adj;
	int			moved_ants;

	adj = g_farm.end->adj;
	moved_ants = 0;
	while (adj)
	{
		if (adj->node->in_path)
			moved_ants += move(adj->node, g_farm.end);
		adj = adj->next;
	}
	return (moved_ants);
}

static int	push_ants(void)
{
	t_adj_lst	*adj;
	int			moved_ants;

	adj = g_farm.start->out;
	moved_ants = 0;
	while (adj && g_farm.next_ant <= g_farm.ants_number)
	{
		if (adj->node->in_path &&
			(g_farm.ants_number - g_farm.next_ant + 1 >=
			 adj->node->dist - g_min_dist))
		{
			ft_printf("L%d-%s ", g_farm.next_ant, adj->node->id);
			adj->node->ant = g_farm.next_ant++;
			moved_ants++;
		}
		adj = adj->next;
	}
	return (moved_ants);
}

void	escort_ants(void)
{
	int	ants_on_road;

	sort_paths();
	ants_on_road = 1;
	g_farm.next_ant = 1;
	while (ants_on_road)
	{
		ants_on_road = pull_ants();
		ants_on_road = push_ants() || ants_on_road;
		ft_printf("\n");
	}
}
