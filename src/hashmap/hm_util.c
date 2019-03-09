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

t_hment			*new_hmentry(const char *key, const char *value)
{
	t_hment	*new;
	char	*new_key;
	char	*new_val;

	new = malloc(sizeof(t_hment));
	new_key = ft_strdup(key);
	new_val = ft_strdup(value);
	if (!new || !new_key || !new_val)
	{
		free((void *)new);
		free((void *)new_key);
		free((void *)new_val);
		return (NULL);
	}
	new->prev = NULL;
	new->next = NULL;
	new->key = new_key;
	new->value = new_val;
	return (new);
}

void			del_hmentry(t_hment *ent)
{
	if (ent->prev)
		ent->prev->next = ent->next;
	if (ent->next)
		ent->next->prev = ent->prev;
	free((void *)(ent->key));
	free((void *)(ent->value));
	free((void *)ent);
}
