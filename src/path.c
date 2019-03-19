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
	lst = g_farm.end->in;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}



static int			add_direct_link(t_node *from, t_node *node_to)
{
	t_adj_lst	*link_1;
	t_adj_lst	*link_2;

	if ((link_1 = malloc(sizeof(t_adj_lst))) == NULL ||
		(link_2 = malloc(sizeof(t_adj_lst))) == NULL)
	{
		perror("lem-in: ");
		exit(1);
	}
	link_1->node = node_to;
	link_1->next = from->out;
	from->out = link_1;
	link_2->node = from;
	link_2->next = node_to->in;
	node_to->in = link_2;
	return (1);
}

// makes path from g_farm.start to n (in reverse order)
int	make_path(t_node *n)
{
	int	dist;

	dist = n->dist;
ft_printf("  Make path: %s ", n->id); //debug
	while (n->prev)
	{
		add_direct_link(n->prev, n);
		n->in_path = 1;
		n->dist = dist++;
		n = n->prev;
ft_printf("<-- %s ", n->id); //debug
	}
ft_printf("\n");
	return (1);
}

// if path from node 'n' to node 'end' found - return 1, otherwise return 0
int	find_shortest_path(t_node *n, t_node *dst)
{
	t_queue		*queue;
	t_adj_lst	*tmp;
	int			path_found;

	path_found = 0;
	queue = init_queue(n);
	while (queue->lst && !path_found)
	{
		tmp = queue->lst->node->adj;
		while (tmp && !path_found)
		{
			if (tmp->node == dst)
			{
				dst->prev = queue->lst->node;
				path_found = make_path(tmp->node);
			}
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

static int		link_exists(t_node *n1, t_node *n2)
{
	t_adj_lst	*lst;

	lst = n1->out;
	while (lst)
	{
		if (lst->node == n2)
			return (1);
		lst = lst->next;
	}
	lst = n1->in;
	while (lst)
	{
		if (lst->node == n2)
			return (1);
		lst = lst->next;
	}
	return (0);
}

int	find_alternative_path(t_node *n)
{
	t_queue		*queue;
	t_adj_lst	*tmp;
	int			path_found;

//  ft_printf("Searching alternative path from %s\n", n->id);
	path_found = 0;
	queue = init_queue(n);
	while (queue->lst && !path_found)
	{
// ft_printf("Searching alternative path %s\n",
	// queue->lst->node->id, queue->lst->node->dist);
		tmp = queue->lst->node->adj;
		while (tmp && !path_found)
		{
// ft_printf("    Trying alternative path %s V%d P%d D%d\n",
	// tmp->node->id, tmp->node->visit, tmp->node->in_path, tmp->node->dist);

			if ((tmp->node == g_farm.end && !link_exists(queue->lst->node, tmp->node)) ||
				(queue->lst->node != g_farm.start &&
				tmp->node->in_path && tmp->node->dist < n->dist &&
				!link_exists(queue->lst->node, tmp->node)))
			{
// ft_printf("    Adding path from %s to %s\n", n->id, tmp->node->id);
				tmp->node->prev = queue->lst->node;
				path_found = make_path(tmp->node);
			}
// ft_printf("    Failed\n");`
			queue_add(tmp->node, queue->lst->node, queue);
			tmp = tmp->next;
		}
		queue_next(queue);
	}
// print_hashmap(g_farm.map);
	free_queue(queue);
	refresh_graph(n);
	return (path_found);
}

int		has_empty_adjacent(t_node *n)
{
	t_adj_lst	*lst;

	lst = n->adj;
	while (lst)
	{
		if (lst->node->in_path == 0 || lst->node == g_farm.end)
			return (1);
		lst = lst->next;
	}
	return (0);
}

// for update distance only
// identical to original queue_update() except check for node->in_path
static void	queue_add_path(t_node *node, t_node *prev, t_queue *queue)
{
	t_adj_lst	*new;

	if (node->visit)
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

void	update_distance(t_node *n)
{
	t_queue		*queue;
	t_adj_lst	*tmp;
	// int			path_found;

	// path_found = 0;
	g_farm.end->dist = 0;
	queue = init_queue(n);
	while (queue->lst)
	{
		tmp = queue->lst->node->in;
		while (tmp)
		{
			if (tmp->node != g_farm.start && tmp->node->visit == 0)
			{
				tmp->node->dist = queue->lst->node->dist + 1;
				queue_add_path(tmp->node, queue->lst->node, queue);
			}
			tmp = tmp->next;
		}
		queue_next(queue);
	}
	free_queue(queue);
	refresh_graph(n);
}

void	find_all_paths(t_node *n)
{
	t_adj_lst	*lst;

	if (n == g_farm.end)
		return ;
	while (find_alternative_path(n))
		;
	lst = n->out;
	while (lst)
	{
		if (has_empty_adjacent(lst->node) )
			find_all_paths(lst->node);
		lst = lst->next;
	}
}
