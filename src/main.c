// header

#include "lemin.h"


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
				ft_printf("Hashmap[%d]: %s\n", i, tmp->key);
				t_node *n = NODE(tmp->value);
				ft_printf("Node: %s(%d, %d) ->", n->id, n->x, n->y);
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

int	main(void)
{
	if (!make_farm())
		return (1);

	while (g_input)
	{
		t_inp_lst *tmp = g_input->next;
		ft_printf("INPUT: %s\n", g_input->str);

		free((void *)(g_input->str));
		free((void *)g_input);

		g_input = tmp;
	}
/*
print_hashmap(g_farm.map);
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
//	escort_ants(farm, path_list);

//	free_all_data();

//system("leaks -quiet lem-in");
	return (0);
}
