/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 19:50:54 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/18 19:55:47 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *from, const char *to)
{
	char	*new;

	if (to < from || (new = malloc(to - from + 1)) == NULL)
		return (NULL);
	ft_strncpy(new, from, to - from);
	new[to - from] = '\0';
	return (new);
}
