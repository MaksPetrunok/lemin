/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 19:53:39 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/06 18:50:15 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Frees initial *ptr, allocates size bytes and returns pointer to allocated
** memory. All data from *ptr copied to newly allocated memory.
*/

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*tmp;

	if (new_size == 0)
	{
		free(ptr);
		return (0);
	}
	if (new_size <= old_size && ptr != 0)
		return (ptr);
	if ((tmp = malloc(new_size)) == 0)
		return (ptr);
	ft_memcpy(tmp, ptr, old_size);
	free(ptr);
	return (tmp);
}
