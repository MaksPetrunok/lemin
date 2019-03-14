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
				ft_printf("\n");
				tmp = tmp->next;
			}
		}
	}
	ft_printf("--------- End hashmap ---------\n");
}

/*
 * Max number of paths = MIN(N_START, N_ENT),
 * where N_START and N_END are numbers
 * of adjacent nodes at start and end nodes respectively.
 *
 * 1. Find all possible paths:
 * for each start_node in start.adj_lst
 *   for each end_node in end.adj_lst
 *     find_path(start_node, end_node)
 *   next end_node
 * next start_node
 *
 * 2. Sort obtained paths in (1) per path length.
 *
 * 3. Set paths into groups, so 1 group contains bunch of non-crossing paths.
 *
 *
 * BFS:
 * Queue = Start.adj_lst
 * for each node in queue
 *   if node == end
 *     return true
 *   else if !empty(node.adj_lst)
 *     queue.add(node.adj_lst)
 *   else
 *     return false
*/

int	main(void)
{
	int	path_exists;

	if (!make_farm())
		return (1);
	path_exists = 0;
	while (bfs(g_farm.start))
	{
		path_exists = 1;
ft_printf("-------------------------------------------------------------\n");
	}
	if (!path_exists)
	{
		ft_dprintf(2, "lem-in: there is no path between start and end rooms\n");
		exit(1);
	}

	while (g_input)
	{
		t_inp_lst *tmp = g_input->next;
		ft_printf("INPUT: %s\n", g_input->str);

		free((void *)(g_input->str));
		free((void *)g_input);

		g_input = tmp;
	}
//print_hashmap(g_farm.map);

/*
ft_printf("Start: %s\n", g_farm.start ? g_farm.start->id : "NULL");
ft_printf("End: %s\n", g_farm.end ? g_farm.end->id : "NULL");
*/

/*
	2. Search path(s), sort in accending order per length.
	If no path connecting ##start and ##end found, report error.
*/

//	if ((path_list = find_paths(farm)) == 0)
//	{
//		// free farm and any other data
//		return (1);
//	}

/*
	Print provided farm data and escort ants to the exit.
*/
//	print_data(); // number of ants, rooms, links
	ft_printf("\n");
	escort_ants();

//	free_all_data();

//system("leaks -quiet lem-in");
	return (0);
}
