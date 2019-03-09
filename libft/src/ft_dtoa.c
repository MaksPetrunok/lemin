/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 19:38:45 by mpetruno          #+#    #+#             */
/*   Updated: 2018/10/23 14:31:37 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	get_float_str(double n, char *buff, int precision)
{
	int		i;

	i = 0;
	n = (n < 0) ? -n : n;
	buff[i++] = (precision == 0) ? '\0' : '.';
	while (precision > 0)
	{
		n = n * 10;
		buff[i++] = (int)n + '0';
		n = n - (double)(buff[i - 1] - '0');
		precision--;
	}
	buff[i] = '\0';
	while (--i > 0 && n * 10 > 4)
	{
		buff[i] += (buff[i + 1] == '\0') ? 1 : 0;
		if (buff[i + 1] == '9' + 1)
		{
			buff[i]++;
			buff[i + 1] = '0';
		}
	}
	if (buff[1] == '9' + 1)
		return ((buff[1] = '0') == '0');
	return (0);
}

void		ft_dtoa(double n, int precision, char *buff)
{
	long int	integer;
	char		s_int[65];
	char		s_float[65];
	char		*res;

	precision = (precision < 0) ? 0 : precision;
	integer = (long int)n;
	if (get_float_str(n - (double)integer, s_float, precision))
		integer++;
	ft_lltoa_base(integer, 10, 0, s_int);
	res = ft_strjoin(s_int, s_float);
	ft_strcpy(buff, res);
	free((void *)res);
}
