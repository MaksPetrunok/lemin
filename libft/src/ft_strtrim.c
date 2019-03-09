/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 11:30:45 by mpetruno          #+#    #+#             */
/*   Updated: 2018/06/18 20:48:45 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

char		*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*p;

	i = 0;
	if (!s)
		return (0);
	while (is_space(s[i]))
		i++;
	start = i;
	end = i;
	while (s[i])
	{
		if (!is_space(s[i]))
			end = i + 1;
		i++;
	}
	p = (char *)malloc(end - start + 1);
	if (p == 0)
		return (0);
	ft_strncpy(p, &s[start], end - start);
	p[end - start] = '\0';
	return (p);
}
