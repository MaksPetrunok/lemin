/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 15:00:06 by mpetruno          #+#    #+#             */
/*   Updated: 2018/06/10 16:05:42 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	reverse(char *str)
{
	int		len;
	int		i;
	char	buff;

	len = (int)ft_strlen(str);
	i = 0;
	while (i < len / 2)
	{
		buff = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = buff;
		i++;
	}
}

static	int		get_size(int n)
{
	int	size;

	size = (n <= 0) ? 1 : 0;
	while (n != 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char			*ft_itoa(int n)
{
	char	*res;
	char	sign;
	int		i;

	res = ft_strnew(get_size(n));
	if (res == 0)
		return (0);
	*res = '0';
	if (n == 0)
		return (res);
	sign = n < 0;
	i = 0;
	while (n != 0)
	{
		res[i++] = '0' + ((sign) ? -(n % 10) : n % 10);
		n = n / 10;
	}
	res[i] = (sign) ? '-' : '\0';
	reverse(res);
	return (res);
}
