/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 22:53:22 by mpetruno          #+#    #+#             */
/*   Updated: 2018/06/18 20:47:42 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin3(char const *s1, char const *s2, const char *s3)
{
	char	*p;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	if (!s1 || !s2 || !s3)
		return (0);
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	len3 = ft_strlen((char *)s3);
	p = (char *)malloc(len1 + len2 + len3 + 1);
	if (p == 0)
		return (0);
	ft_strcpy(p, s1);
	ft_strcpy(p + len1, s2);
	ft_strcpy(p + len1 + len2, s3);
	p[len1 + len2 + len3] = '\0';
	return (p);
}
