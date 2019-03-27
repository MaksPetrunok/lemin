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
	for (int i = 0; i < hm->size; i++)
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

static void	read_from_file(int ac, char **args)
{
	int	fd;

	if (ac > 2)
	{
		ft_dprintf(2, "lem-in: too much arguments\n");
		exit(1);
	}
	if ((fd = open(args[1], O_RDONLY)) == -1)
	{
		ft_dprintf(2, "lem-in: cannot read file '%s'\n", args[1]);
		exit(1);
	}
	if (dup2(fd, 0) == -1)
	{
		ft_dprintf(2, "lem-in: I/O redirection error occured\n");
		exit(1);
	}
	else
		close(fd);
}

static void	print_input(void)
{
	t_inp_lst *tmp;

	while (g_input)
	{
		tmp = g_input->next;
		ft_printf("%s\n", g_input->str);
		free((void *)(g_input->str));
		free((void *)g_input);
		g_input = tmp;
	}
}

int			main(int ac, char **av)
{
	if (ac > 1)
		read_from_file(ac, av);
	if (!make_farm())
		return (1);
	g_farm.end->dist = 0;
	if (!find_shortest_path(g_farm.start, g_farm.end))
	{
		ft_dprintf(2, "lem-in: there is no path between start and end rooms\n");
		exit(1);
	}
	while (find_alternative_path(g_farm.start))
		;
	g_farm.inputs = count_inputs();
	sort_paths(g_farm.start);
	refresh_graph(g_farm.start);
	update_distance(g_farm.end);
	print_input();
	escort_ants();
// system("leaks -quiet lem-in");
	return (0);
}
