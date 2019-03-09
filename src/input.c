// header

#include "lemin.h"

int	main(void)
{
/*
	1. Read input, validate input and make graph for farm.
	Pre-validate input for double-##start/##end, missing data etc..
	Use hashtable for faster access to nodes?
*/

	if ((farm = read_input()) == NULL)
		return (1);

/*
	2. Search path(s), sort in accending order per length.
	If no path connecting ##start and ##end found, report error.
*/

	if ((path_list = find_paths(farm)) == 0)
	{
		// free farm and any other data
		return (1);
	}

/*
	Escort ants to the exit.
*/
	escort_ants(farm, path_list);

	free_all_data();
	return (0);
}
