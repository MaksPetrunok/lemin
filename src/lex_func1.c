/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_func1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 13:35:39 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/12 13:35:46 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	set_err(char *str)
{
	ft_dprintf(2, "lem-in: unexpected token '%s'\n",
			*str == '\0' ? "empty line" : str);
	free((void *)str);
	return (-1);
}

int	set_ants(char *str)
{
	if (!ft_isnumeric(str))
	{
		ft_dprintf(2, "lem-in: number of ants is not an integer\n");
		return (-1);
	}
	g_farm.ants_number = ft_atoi(str);
	if (g_farm.ants_number > 0)
	{
		add_input(str);
		return (1);
	}
	ft_dprintf(2, "lem-in: incorrect number of ants provided\n");
	return (-1);
}

int	set_room(char *str)
{
	t_node	*node;

	if ((node = init_node(str)) == NULL)
		return (-1);
	if (!hmap_set(node->id, node, g_farm.map))
	{
		free((void *)(node->id));
		free((void *)node);
		perror("lem-in: ");
		return (-1);
	}
	add_input(str);
	return (1);
}
