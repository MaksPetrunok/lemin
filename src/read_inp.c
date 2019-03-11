// header

#include "lemin.h"

/*
1. Read line, if not comment - add to list.
1.1. Count number of ##start and ##end.
1.2. If there is more than one ##start or ##end - finish.

*/

t_inp_lst	*input = NULL;

int	add_input(char *str)
{
	t_inp_lst			*new;
	static t_inp_lst	*last = NULL;

	if ((new = malloc(sizeof(t_inp_lst))) == NULL)
	{
		perror("lem-in: ");
		return (0);
	}
	new->str = str;
	new->next = NULL;
	if (last)
		last->next = new;
	last = new;
	if (!input)
		input = new;
	return (1);
}

/*
** Reads input lines and stores them (except comments) in list input.
int		read_input(void)
{
	char		*str;
	t_inp_lst	*lst;
	t_inp_lst	*new;

	lst = NULL;
	while (get_next_line(0, &str) > 0)
	{
		if (*str == '#' && *(str + 1) != '#')
		{
			free((void *)str);
			continue ;
		}
		if ((new = new_inp(str)) == NULL)
		{
			free((void *)str);
			return (0);
		}
		if (lst)
			lst->next = new;
		else
			lst = new;
		lst = (lst->next != NULL) ? lst->next : lst;
		input = (input == NULL) ? lst : input;
	}
	return (1);
}
*/
