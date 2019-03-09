/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 15:58:07 by mpetruno          #+#    #+#             */
/*   Updated: 2018/06/18 20:50:54 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	limit;

	if (*needle == 0)
		return ((char *)haystack);
	if (len == 0)
		return (0);
	limit = len;
	j = 0;
	while (haystack[j] && len-- > 0)
	{
		i = 0;
		while (haystack[i + j] == needle[i] && i + j < limit)
		{
			if (needle[i + 1] == 0)
				return ((char *)(haystack + j));
			if (haystack[i + j] == 0)
				return (0);
			i++;
		}
		j++;
	}
	return (0);
}
