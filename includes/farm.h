/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   farm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 17:49:43 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/14 21:06:01 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FARM_H
# define FARM_H

# include "libft.h"
# include "hashmap.h"

# define S_ANT	0
# define S_ROOM	1
# define S_LINK	2

# define L_ANT	0
# define L_ROOM	1
# define L_LINK	2
# define L_CMD	3
# define L_ERR	4
# define L_COMM	5

# define NODE(X) (t_node *)X

typedef struct s_adj_lst	t_adj_lst;
typedef struct s_node		t_node;
typedef struct s_queue		t_queue;
typedef struct s_ant_queue		t_ant_queue;
typedef struct s_ant		t_ant;

struct			s_ant
{
	int			id;
	t_node		*node;
	t_node		*prev_node;
	t_ant		*next;
};

struct			s_ant_queue
{
	t_ant		*lst;
	t_ant		*last;
};


struct			s_node
{
	char		*id;
	int			x;
	int			y;
	int			ant;
	int			in_path;
	int			visit;
	int			alt_path;
	int			dist;
	t_node		*lock;
	t_node		*prev;
	t_adj_lst	*adj;
	t_adj_lst	*in;
	t_adj_lst	*out;
};

struct			s_queue
{
	t_adj_lst	*lst;
	t_adj_lst	*last;
};

struct			s_adj_lst
{
	t_node		*node;
	t_adj_lst	*next;
};

typedef struct		s_farm
{
	int				ants_number;
	int				next_ant;
	int				path_id;
	int				inputs;
	int				outputs;
	t_node			*start;
	t_node			*end;
	t_hashmap		*map;
}					t_farm;

typedef int			(*t_inp_func)(char *str);

typedef struct		s_state_trans
{
	int				state;
	t_inp_func		func;
}					t_state_trans;


/*
** farm.c
*/
int				make_farm(void);
int				add_input(char *str);

/*
** node.c
*/
t_node			*init_node(const char *str);
int				add_link(t_node *node, t_node *adj);
void			remove_link(t_node *node, t_adj_lst *adj);
void			free_node(t_node *node);

/*
** lex_func1.c
*/
int					set_comment(char *str);
int					set_err(char *str);
int					set_ants(char *str);
int					set_room(char *str);

/*
** lex_func2.c
*/
int					set_link(char *str);
int					set_cmd(char *str);

/*
** token_check.c
*/
int					is_room(const char *str);
int					is_link(const char *str);



#endif
