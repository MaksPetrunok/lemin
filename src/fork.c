/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 20:31:16 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/14 21:08:39 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	remove_out_link(t_adj_lst **from, t_node *to)
{
	t_adj_lst	*tmp;
	t_adj_lst	*rm;

	tmp = *from;
	if ((*from)->node == to)
	{
		*from = (*from)->next;
		free((void *)tmp);
	}
	else
	{
		while (tmp && tmp->next)
		{
			if (tmp->next->node == to)
			{
				rm = tmp->next;
				tmp->next = tmp->next->next;
				free((void *)rm);
				break ;
			}
			tmp = tmp->next;
		}
	}
}

static int	has_out_forks(t_node *n)
{
	if (n == g_farm.start)
		return (0);
	if (n->out && n->out->next != NULL)
		return (1);
	return (has_out_forks(n->in->node));
}
/*
static t_adj_lst	*find_out_link_for(t_node *n, t_adj_lst *lst)
{
	while (lst)
	{
		if (lst->node == n)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
*/
static void	remove_input_fork(t_node *n)
{
	t_adj_lst	*lst;
	t_adj_lst	*valid;
	t_adj_lst	*next;

//ft_printf("Input fork in %s\n", n->id);
	lst = n->in;
	while (lst)
	{
//ft_printf("    fork: %s\n", lst->node->id);
		if (!has_out_forks(lst->node) || lst->next == NULL)
		{
			valid = lst;
//ft_printf("    valid: %s\n", lst->node->id);
			break ;
		}
		lst = lst->next;
	}
	lst = n->in;
	while (lst)
	{
//ft_printf("LOOP\n");
		// remove output link from lst->node->out
		if (lst != valid)
		{
ft_printf("Removing: %s-%s\n", n->id, lst->node->id);
			remove_out_link(&(lst->node->out), n);
			next = lst->next;
			remove_link(n, lst);
			lst = next;
		}
else
{
ft_printf("Skip: %s\n", lst->node->id);
			lst = lst->next;
}
//		else
//			lst = lst->next;
	}
//exit(0);
	n->in = valid;
	valid->next = NULL;
//ft_printf("Link remain: %s - %p\n", n->in->node->id, n->in->next);
}

// if path from node 'n' to node 'end' found - return 1, otherwise return 0
void			unfork(t_node *n)
{
	t_queue		*queue;
	t_adj_lst	*tmp;

	n->dist = 0;
	queue = init_queue(n);
	while (queue->lst) // && has_unvisited(start) && has_unvisited(end))
	{
		tmp = queue->lst->node->out;
		while (tmp)
		{
//			if (tmp->node != g_farm.end && tmp->node->in &&
//				tmp->node->in->next != NULL)
//				remove_input_fork(tmp->node);
				queue_add(tmp->node, queue->lst->node, queue);
			tmp = tmp->next;
		}
			if (queue->lst->node != g_farm.end && queue->lst->node->in &&
				queue->lst->node->in->next != NULL)
				remove_input_fork(queue->lst->node);
		queue_next(queue);
	}
	free_queue(queue);
}
