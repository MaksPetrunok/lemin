// header

#ifndef LEMIN_H
# define LEMIN_H

# include <stdio.h>
# include <errno.h>
# include "libft.h"
# include "hashmap.h"
# include "farm.h"

# define MIN(X, Y)	(X < Y) ? X : Y
# define MAX(X, Y)	(X > Y) ? X : Y

typedef struct s_inp_lst	t_inp_lst;

struct			s_inp_lst
{
	char		*str;
	t_inp_lst	*next;
};

extern t_farm		g_farm;
extern t_inp_lst	*g_input;

int					add_input(char *str);
void				relink(t_node *n);
void				escort_ants(void);


/*
** fork.c
*/
void				unfork(t_node *n);

/*
** queue.c
*/
t_queue	*init_queue(t_node *node);
void	queue_add(t_node *node, t_node *prev, t_queue *queue);
void	free_queue(t_queue *q);
void	queue_next(t_queue *queue);
int		find_paths(t_node *n);

/*
** sort.c
*/
void	sort_paths(t_node *n);

/*
** ant_queue.c
*/
t_ant_queue			*init_ants(void);
void				ant_queue_add(int id, t_node *node, t_ant_queue *queue);
void				ant_free_queue(t_ant_queue *q);
void				ant_queue_next(t_ant_queue *queue);
void				ant_queue_push(t_ant_queue *queue);


#endif
