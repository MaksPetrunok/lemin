/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 16:30:51 by mpetruno          #+#    #+#             */
/*   Updated: 2018/10/23 14:24:27 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ulltoa_base(unsigned long long int n, int base, int capital, char *b)
{
	char	*symbols;
	char	buff[65];
	int		i;

	i = 64;
	buff[i--] = '\0';
	if (n == 0)
		buff[i--] = '0';
	symbols = (capital) ? "0123456789ABCDEF" : "0123456789abcdefgh";
	while (n != 0)
	{
		buff[i--] = symbols[n % base];
		n /= base;
	}
	i++;
	while (buff[i])
		*b++ = buff[i++];
	*b = '\0';
}
