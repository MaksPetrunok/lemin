/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relink.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 20:31:16 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/14 21:08:39 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_adj_lst	*move_link(t_adj_lst *link, t_adj_lst **lst)
{
	t_adj_lst	*tmp;

	tmp = link->next; // next elem after one is being moved
	link->next = *lst;
	*lst = link;
	return (tmp);
}

void	relink(t_node *n)
{
	t_adj_lst	*lst;

	if (n == g_farm.end || n->adj == NULL)
		return ;
	lst = n->adj;
	while (lst)
	{
		if (lst->node->dist > n->dist)
			lst = move_link(lst, &(n->out));
		else if (lst->node->dist < n->dist)
			lst = move_link(lst, &(n->in));
		else
			lst = lst->next;
	}
	n->adj = NULL;
	lst = n->out;
	while (lst)
	{
		relink(lst->node);
		lst = lst->next;
	}
}
