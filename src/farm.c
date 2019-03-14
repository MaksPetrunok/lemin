/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   farm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 09:47:29 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/14 21:07:05 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_farm		g_farm;
t_inp_lst	*g_raw_input = NULL;
t_inp_lst	*g_input = NULL;

static t_state_trans	g_fsm_table[3][6] =
{
	[S_ANT][L_ANT] = {S_ROOM, &set_ants},
	[S_ANT][L_ROOM] = {S_ROOM, &set_err},
	[S_ANT][L_LINK] = {S_ROOM, &set_err},
	[S_ANT][L_CMD] = {S_ROOM, &set_err},
	[S_ANT][L_ERR] = {S_ROOM, &set_err},
	[S_ANT][L_COMM] = {S_ANT, NULL},

	[S_ROOM][L_ANT] = {S_ROOM, &set_err},
	[S_ROOM][L_ROOM] = {S_ROOM, &set_room},
	[S_ROOM][L_LINK] = {S_LINK, &set_link},
	[S_ROOM][L_CMD] = {S_ROOM, &set_cmd},
	[S_ROOM][L_ERR] = {S_ROOM, &set_err},
	[S_ROOM][L_COMM] = {S_ROOM, NULL},

	[S_LINK][L_ANT] = {S_ROOM, &set_err},
	[S_LINK][L_ROOM] = {S_ROOM, &set_err},
	[S_LINK][L_LINK] = {S_LINK, &set_link},
	[S_LINK][L_CMD] = {S_LINK, NULL},
	[S_LINK][L_ERR] = {S_LINK, &set_err},
	[S_LINK][L_COMM] = {S_LINK, NULL}
};

int			add_input(char *str)
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
	if (!g_input)
		g_input = new;
	return (1);
}

static int	get_input_type(const char *str)
{
	if (ft_isnumeric(str))
		return (L_ANT);
	else if (*str == '#' && *(str + 1) != '#')
		return (L_COMM);
	else if (*str == '#' && *(str + 1) == '#')
		return (L_CMD);
	else if (is_link(str))
		return (L_LINK);
	else if (is_room(str))
		return (L_ROOM);
	else
		return (L_ERR);
}

static int	check_farm(void)
{
	if (!g_farm.start || !g_farm.end)
	{
		ft_dprintf(2, "lem-in: %s room is not defined\n",
				g_farm.start ? "##end" : "##start");
		return (0);
	}
	return (1);
}

int			make_farm(void)
{
	char		*str;
	t_inp_func	func;
	int			state;
	int			inp_sig;

	if ((g_farm.map = init_hashmap(2024)) == NULL)
	{
		perror("lem-in: ");
		return (0);
	}
	state = S_ANT;
	while (get_next_line(0, &str) > 0)
	{
		inp_sig = get_input_type(str);
		if ((func = g_fsm_table[state][inp_sig].func) == 0)
			free((void *)str);
		else if (func(str) < 0)
			return (0);
		state = g_fsm_table[state][inp_sig].state;
	}
	g_farm.path_id = 1;
	return (check_farm());
}
