// header

#include "lemin.h"

t_farm		g_farm;
t_inp_lst	*g_raw_input = NULL;

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

int	set_err(char *str)
{
	// add 'empty line' instead of '' ?
	ft_dprintf(2, "lem-in: unexpected token '%s'\n", str);
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
ft_printf("set ants: %d\n", g_farm.ants_number);
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
	return (1);
}

int	is_room(const char *str)
{
	char	*x;
	char	*y;

	if (*str == 'L' || *str == ' ')
		return (0);
	else if ((x = ft_strchr(str, ' ')) == NULL ||
			(y = ft_strchr(x + 1, ' ')) == NULL)
		return (0);
	else if (*(x + 1) == '\0' || *(y + 1) == '\0')
		return (0);
	x++;
	y++;
	while (*x && *x != ' ')
	{
		if (!ft_isdigit(*x++))
			return (0);
	}
	while (*y)
	{
		if (!ft_isdigit(*y++))
			return (0);
	}
	return (1);
}

int set_cmd(char *str)
{
	char	*tmp;
	t_node	*node;

	if (!ft_strequ(str, "##start") && !ft_strequ(str, "##end"))
		return (1);
	if (get_next_line(0, &tmp) <= 0 || !is_room(tmp))
	{
// handle empty tmp
		ft_dprintf(2, "lem-in: unexpected token '%s'\n", tmp ? tmp : "EOF");
		free((void *)tmp);
		return (-1);
	}
	if ((node = init_node(tmp)) == NULL)
		return (-1);
	if (!hmap_set(node->id, node, g_farm.map))
	{
		free((void *)(node->id));
		free((void *)node);
		perror("lem-in: ");
		return (-1);
	}
// !!! check for duplicates
//	set_node(node, str); // set start or end to current node
	if (ft_strequ(str, "##start"))
		g_farm.start = node;
	else if (ft_strequ(str, "##end"))
		g_farm.end = node;
	return (1);
}

int	set_link(char *str)
{
	ft_printf("set link: %s\n", str);
	return (1);
}

int	get_input_type(const char *str)
{
	if (ft_isnumeric(str))
		return (L_ANT);
	else if (*str == '#' && *(str + 1) != '#')
		return (L_COMM);
	else if (*str == '#' && *(str + 1) == '#')
		return (L_CMD);
	else if (ft_strchr(str, '-') && !ft_strchr(str, ' '))
		return (L_LINK);
	else if (is_room(str))
		return (L_ROOM);
	else
		return (L_ERR);
}

int	make_farm(void)
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
		{
			// free all data here or in main?
			return (0);
		}
		state = g_fsm_table[state][inp_sig].state;
	}
	return (1);
}
