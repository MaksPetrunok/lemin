/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   farm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 09:47:29 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/12 13:47:55 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

extern int	g_room_state;

int			set_cmd(char *str)
{
	if (!ft_strequ(str, "##start") && !ft_strequ(str, "##end"))
	{
		free((void *)str);
		return (1);
	}
	if (ft_strequ(str, "##start"))
	{
		if (g_farm.start != NULL)
		{
			ft_dprintf(2, "lem-in: duplicate ##start found");
			exit(1);
		}
		g_room_state = 1;
	}
	else if (ft_strequ(str, "##end"))
	{
		if (g_farm.end != NULL)
		{
			ft_dprintf(2, "lem-in: duplicate ##end found");
			exit(1);
		}
		g_room_state = 2;
	}
	add_input(str);
	return (1);
}

static void	check_room_state(void)
{
	if (g_room_state != 0)
	{
		ft_dprintf(2,
			"lem-in: syntax error - room token expected after '##%s'\n",
			(g_room_state == 1) ? "start" : "end");
		exit(1);
	}
}

int			set_link(char *str)
{
	char	*id1;
	char	*id2;
	t_node	*n1;
	t_node	*n2;

	check_room_state();
	if ((id1 = ft_strdup(str)) == NULL)
	{
		perror("lem-in: ");
		exit(1);
	}
	id2 = ft_strchr(id1, '-');
	*id2++ = '\0';
	if ((n1 = NODE(hmap_get(id1, g_farm.map))) == NULL ||
		(n2 = NODE(hmap_get(id2, g_farm.map))) == NULL)
	{
		ft_dprintf(2, "lem-in: room '%s' not found\n", n1 ? id2 : id1);
		exit(1);
	}
	free((void *)id1);
	if (!add_link(n1, n2))
		return (-1);
	add_input(str);
	return (1);
}
