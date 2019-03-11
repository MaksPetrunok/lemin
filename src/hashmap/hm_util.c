/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 17:00:30 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 18:23:32 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"

unsigned long	hash(const char *str)
{
	unsigned long	hash;

	hash = 5381;
	while (*str)
		hash = ((hash << 5) + hash) + *str++;
	return (hash);
}

t_hment			*new_hmentry(const char *key, VAL_TYPE *value)
{
	t_hment		*new;
	char		*new_key;

	if (!key || !value)
	{
		ft_dprintf(2, "hashmap: setting NULL pointer as a key\n");
		return (NULL);
	}
	new = malloc(sizeof(t_hment));
	new_key = ft_strdup(key);
	if (!new || !new_key)
	{
		free((void *)new);
		free((void *)new_key);
		return (NULL);
	}
	new->prev = NULL;
	new->next = NULL;
	new->key = new_key;
	new->value = value;
	return (new);
}

void			del_hmentry(t_hment *ent)
{
	if (ent->prev)
		ent->prev->next = ent->next;
	if (ent->next)
		ent->next->prev = ent->prev;
	free((void *)(ent->key));
	free((void *)ent);
}
