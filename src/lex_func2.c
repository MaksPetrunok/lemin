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

static int	set_node(t_node *n, char *dst)
{
	char	*msg;

	msg = NULL;
	if (ft_strequ(dst, "##start") && g_farm.start != NULL)
		msg = "duplicate ##start found";
	else if (ft_strequ(dst, "##end") && g_farm.end != NULL)
		msg = "duplicate ##end found";
	if (msg)
	{
		ft_dprintf(2, "lem-in: %s\n", msg);
		return (0);
	}
	if (ft_strequ(dst, "##start"))
		g_farm.start = n;
	else if (ft_strequ(dst, "##end"))
		g_farm.end = n;
	return (1);
}

int			set_cmd(char *str)
{
	char	*tmp;
	t_node	*node;

	if (!ft_strequ(str, "##start") && !ft_strequ(str, "##end"))
	{
		free((void *)str);
		return (1);
	}
	if (get_next_line(0, &tmp) <= 0 || !is_room(tmp))
	{
		ft_dprintf(2, "lem-in: unexpected token '%s'\n", tmp ? tmp : "EOF");
		exit(1);
	}
	if ((node = init_node(tmp)) == NULL)
		exit(1);
	if (!hmap_set(node->id, node, g_farm.map))
	{
		perror("lem-in: ");
		exit(1);
	}
	if (!set_node(node, str))
		return (-1);
	add_input(str);
	add_input(tmp);
	return (1);
}

int			set_link(char *str)
{
	char	*id1;
	char	*id2;
	t_node	*n1;
	t_node	*n2;

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
