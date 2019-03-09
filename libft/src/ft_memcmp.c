/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 15:56:01 by mpetruno          #+#    #+#             */
/*   Updated: 2018/06/20 16:53:04 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (void *)s1;
	p2 = (void *)s2;
	i = 0;
	while (i < n)
	{
		if (*(p1 + i) != *(p2 + i))
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}
