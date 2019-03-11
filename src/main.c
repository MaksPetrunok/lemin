// header

#include "lemin.h"

int	main(void)
{
/*
	1. Read input, validate input and make graph for farm.
	Ignore comments.
	Pre-validate (on the go) input for double-##start/##end. (Double inclusions, wrong format...)
	If ants, ##start, ##end or links are missing - report and exit.
	Store input lines in array.
	Use hashtable for faster access to nodes?
*/
	if (!make_farm())
		return (1);

// debug
	while (g_raw_input)
	{
		t_inp_lst *tmp = g_raw_input->next;
		ft_printf("INPUT: %s\n", g_raw_input->str);

		free((void *)(g_raw_input->str));
		free((void *)g_raw_input);

		g_raw_input = tmp;
	}
ft_printf("Start: %p\n", g_farm.start);
ft_printf("End: %p\n", g_farm.end);

//	if ((farm = read_input()) == NULL)
//		return (1);

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
	return (0);
}
