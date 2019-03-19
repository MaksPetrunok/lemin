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

// static int	g_min_dist = 2000000;

static t_adj_lst	*sort(t_adj_lst *lst)
{
	t_adj_lst	*head;
	t_adj_lst	*tmp;
	t_adj_lst	*iter;

	head = NULL;
	while (lst != NULL)
	{
		tmp = lst;
		// g_min_dist =
		// 	(tmp->node->dist < g_min_dist) ? tmp->node->dist : g_min_dist;
		lst = lst->next;
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
	return (head);
}

void		sort_paths(t_node *node)
{
	t_adj_lst	*lst;

	node->out = sort(node->out);
	node->visit = 1;
	lst = node->out;
	while (lst)
	{
		if (lst->node->visit == 0)
			sort_paths(lst->node);
		lst = lst->next;
	}
}