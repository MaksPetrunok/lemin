/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 17:49:43 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 19:08:08 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_H
# define HASHMAP_H

# include "libft.h"

typedef struct s_hment	t_hment;

struct			s_hment
{
	char		*key;
	char		*value;
	t_hment		*prev;
	t_hment		*next;
};

typedef struct	s_hashmap
{
	int			size;
	t_hment		**list;
}				t_hashmap;

/*
** hashmap.c
*/
t_hashmap		*init_hashmap(int size);
char			*hmap_get(const char *key, t_hashmap *hmap);
int				hmap_set(const char *key, const char *val, t_hashmap *hmap);
int				hmap_del(const char *key, t_hashmap *hmap);
void			free_hashmap(t_hashmap *map);

/*
** hm_util.c
*/
unsigned long	hash(const char *str);
t_hment			*new_hmentry(const char *key, const char *value);
void			del_hmentry(t_hment *ent);

#endif
