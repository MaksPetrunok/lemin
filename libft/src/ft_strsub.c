/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 22:26:17 by mpetruno          #+#    #+#             */
/*   Updated: 2018/06/18 20:46:59 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *p;

	if (!s)
		return (0);
	p = (char *)malloc(len + 1);
	if (p == 0)
		return (0);
	p[len] = '\0';
	return (ft_strncpy(p, (char *)s + start, len));
}
