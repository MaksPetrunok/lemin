/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 17:00:30 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 18:25:46 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"

t_hashmap	*init_hashmap(int size)
{
	t_hashmap	*map;
	int			i;

	if ((map = malloc(sizeof(t_hashmap))) == NULL)
		return (NULL);
	if ((map->list = malloc(sizeof(t_hment) * size)) == NULL)
	{
		free((void *)map);
		return (NULL);
	}
	map->size = size;
	i = 0;
	while (i < size)
		map->list[i++] = NULL;
	return (map);
}

VAL_TYPE	*hmap_get(const char *key, t_hashmap *hmap)
{
	int		index;
	t_hment	*lst;

	if (!key || !hmap)
		return (NULL);
	index = hash(key) % hmap->size;
	lst = hmap->list[index];
	while (lst)
	{
		if (ft_strequ(key, lst->key))
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

int			hmap_set(const char *key, VAL_TYPE *val, t_hashmap *hmap)
{
	int		index;
	t_hment	*ent;

	if (!key || !val || !hmap)
		return (0);
	index = hash(key) % hmap->size;
	ent = hmap->list[index];
	while (ent)
	{
		if (ft_strequ(key, ent->key))
		{
			free((void *)(ent->value));
			ent->value = val;
			return (1);
		}
		ent = ent->next;
	}
	if ((ent = new_hmentry(key, val)) == NULL)
		return (0);
	ent->next = hmap->list[index];
	if (ent->next)
		ent->next->prev = ent;
	hmap->list[index] = ent;
	return (1);
}

int			hmap_del(const char *key, t_hashmap *hmap)
{
	int		index;
	t_hment	*lst;

	if (!key || !hmap)
		return (0);
	index = hash(key) % hmap->size;
	lst = hmap->list[index];
	while (lst)
	{
		if (ft_strequ(key, lst->key))
		{
			if (lst->prev == NULL)
				hmap->list[index] = lst->next;
			del_hmentry(lst);
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

void		free_hashmap(t_hashmap *map)
{
	int		i;
	t_hment	*e;
	t_hment *tmp;

	if (map == NULL)
		return ;
	i = 0;
	while (i < map->size)
	{
		e = map->list[i];
		while (e)
		{
			free((void *)(e->key));
//			free((void *)(e->value));
			tmp = e;
			e = e->next;
			free((void *)tmp);
		}
		i++;
	}
	free((void *)(map->list));
	free((void *)map);
}
