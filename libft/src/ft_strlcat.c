/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 16:00:38 by mpetruno          #+#    #+#             */
/*   Updated: 2018/06/09 20:46:35 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen((char *)src);
	if (dst_len >= dstsize || dstsize == 0)
		return (dstsize + src_len);
	i = 0;
	while (dst[i] && i < dstsize)
		i++;
	dst_len = i;
	while (*src && i < dstsize - 1)
		dst[i++] = *src++;
	dst[i] = '\0';
	return (dst_len + src_len);
}
