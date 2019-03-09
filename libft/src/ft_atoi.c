/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 15:55:04 by mpetruno          #+#    #+#             */
/*   Updated: 2018/06/14 11:15:53 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*is_numeric(char *s)
{
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (ft_isdigit(*s))
		return (s);
	if (*s == '+' && ft_isdigit(*(s + 1)))
		return (s + 1);
	if (*s == '-' && ft_isdigit(*(s + 1)))
		return (s);
	return (0);
}

int				ft_atoi(const char *nptr)
{
	char	sign;
	long	res;
	long	tmp;

	nptr = is_numeric((char *)nptr);
	if (!nptr)
		return (0);
	sign = (*nptr == '-') ? *nptr++ : 0;
	while (*nptr == '0')
		nptr++;
	if (!ft_isdigit(*nptr))
		return (0);
	res = (sign == '-') ? ('0' - *nptr) : (*nptr - '0');
	while (ft_isdigit(*(++nptr)))
	{
		tmp = (res > 0) ? res * 10 + (*nptr ^ '0') : res * 10 - (*nptr ^ '0');
		if ((res > 0 && tmp <= res) || (res < 0 && tmp >= res))
			return ((res < 0) ? 0 : -1);
		if (res > 0)
			res = res * 10 + (*nptr ^ '0');
		else
			res = res * 10 - (*nptr ^ '0');
	}
	return (res);
}
