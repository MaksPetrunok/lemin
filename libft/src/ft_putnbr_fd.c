/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 17:45:23 by mpetruno          #+#    #+#             */
/*   Updated: 2018/06/10 21:30:13 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(int n)
{
	int	res;

	res = 1;
	while (n > 9 || n < -9)
	{
		res *= 10;
		n /= 10;
	}
	return (res);
}

void		ft_putnbr_fd(int n, int fd)
{
	int	pow;
	int	c;

	pow = get_size(n);
	if (n < 0)
		ft_putchar_fd('-', fd);
	while (pow != 0)
	{
		c = n / pow;
		ft_putchar_fd((c < 0) ? '0' - c : '0' + c, fd);
		n = n % pow;
		pow = pow / 10;
	}
}
