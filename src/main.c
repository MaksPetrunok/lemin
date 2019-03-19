/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 20:00:51 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/14 17:53:41 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

// debug function
void	print_hashmap(t_hashmap *hm)
{
	ft_printf("--------- Node hashmap ---------\n");
	for (int i=0; i<hm->size; i++)
	{
		if (hm->list[i])
		{
			t_hment *tmp = hm->list[i];
			while (tmp)
			{
				ft_printf("Hashmap[%d]:	%s | ", i, tmp->key);
				t_node *n = NODE(tmp->value);
				ft_printf("Node: %s(%d, %d) V%d P%d D%d ->",
							n->id, n->x, n->y, n->visit, n->in_path, n->dist);
				t_adj_lst *adj = n->adj;
				while (adj)
				{
					ft_printf(" %s", adj->node->id);
					adj = adj->next;
				}
				ft_printf(" | IN:");
				adj = n->in;
				while (adj)
				{
					ft_printf(" %s", adj->node->id);
					adj = adj->next;
				}
				ft_printf(" | OUT:");
				adj = n->out;
				while (adj)
				{
					ft_printf(" %s", adj->node->id);
					adj = adj->next;
				}
				ft_printf("\n");
				tmp = tmp->next;
			}
		}
	}
	ft_printf("--------- End hashmap ---------\n");
}

int	main(void)
{
	if (!make_farm())
		return (1);

/*
	1. Find shortes path and remove dead ends.
	Add direct links to nodes and dist to end while creating shortest path.
	2. For each node in path, starting from END,
	if node has at leas one adjacent node with in_path == 0:
		2.1. try build path from current node.
			Path is valid if:
				- END node reached or
				- node with dist < current node->dist reached
		2.2. If there are no nodes with adjacent nodes without path - break.
	
*/

ft_printf("Initial graph:\n");
print_hashmap(g_farm.map); // DEBUG

	g_farm.end->dist = 0;
	if (!find_shortest_path(g_farm.start, g_farm.end))
	{
		ft_dprintf(2, "lem-in: there is no path between start and end rooms\n");
		exit(1);
	}
ft_printf("------------ Find All --------------\n");
// find_alternative_path(g_farm.start);
// ft_printf("After 1st alt search:\n");
// print_hashmap(g_farm.map); // DEBUG
// ft_printf("--------------------------------------------\n");

// find_alternative_path(g_farm.start);
// ft_printf("After 2nd alt search:\n");
// print_hashmap(g_farm.map); // DEBUG
// ft_printf("--------------------------------------------\n");

// find_alternative_path(g_farm.start->adj->node);
// ft_printf("After |%d| alt search:\n", g_farm.start->adj->node->id);
// print_hashmap(g_farm.map); // DEBUG
// ft_printf("--------------------------------------------\n");
// // // exit(1);

	find_all_paths(g_farm.start);
	update_distance(g_farm.end);

// ft_printf("n_outputs = %d\n", g_farm.outputs);
// ft_printf("n_inputs = %d\n", g_farm.inputs);

ft_printf("After finding all:\n");
print_hashmap(g_farm.map); // DEBUG


// ft_printf("After BFS evaluation:\n");
// print_hashmap(g_farm.map); // DEBUG
// 	relink(g_farm.start);
// ft_printf("After I/O relinking:\n");
// print_hashmap(g_farm.map); // DEBUG
// 	unfork(g_farm.start);
// ft_printf("After removing input forks:\n");
// print_hashmap(g_farm.map); // DEBUG

sort_paths(g_farm.start);
// ft_printf("After sorting input:\n");
// print_hashmap(g_farm.map); // DEBUG
	while (g_input)
	{
		t_inp_lst *tmp = g_input->next;
		ft_printf("%s\n", g_input->str);

		free((void *)(g_input->str));
		free((void *)g_input);

		g_input = tmp;
	}
	g_farm.inputs = count_inputs();
	escort_ants();
ft_printf("Inputs: %d\n", g_farm.inputs);

//	free_all_data();

//system("leaks -quiet lem-in");
	return (0);
}
