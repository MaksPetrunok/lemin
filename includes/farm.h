/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   farm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 17:49:43 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 19:08:08 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FARM_H
# define FARM_H

# include "libft.h"

typedef struct s_adj_lst	t_adj_lst;

typedef struct	s_node
{
	char		*id;
	int			x;
	int			y;
	t_adj_lst	*adj;
}				t_node;

struct			s_adj_lst
{
	t_node		*node;
	t_adj_lst	*next;
};

/*
** farm.c
*/
t_node			*init_node(const char *id, int x, int y);
void			free_node(t_node *node);

#endif
