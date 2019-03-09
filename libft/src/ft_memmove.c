/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 11:58:22 by mpetruno          #+#    #+#             */
/*   Updated: 2018/06/10 21:22:56 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			i;

	if (src == dst)
		return (dst);
	if (src > dst)
		return (ft_memcpy(dst, src, len));
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = len;
	while (i != 0)
	{
		*(d + i - 1) = *(s + i - 1);
		i--;
	}
	return (dst);
}
