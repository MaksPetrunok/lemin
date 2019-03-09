/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 16:30:51 by mpetruno          #+#    #+#             */
/*   Updated: 2018/10/10 14:16:23 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lltoa_base(long long int n, int base, int capital, char *new_buff)
{
	char	*symbols;
	char	buff[65];
	int		i;
	char	negative;
	int		index;

	i = 64;
	buff[i--] = '\0';
	if (n == 0)
		buff[i--] = '0';
	symbols = (capital) ? "0123456789ABCDEF" : "0123456789abcdefgh";
	negative = (base == 10 && n < 0);
	while (n != 0)
	{
		index = n % base;
		buff[i--] = symbols[(index < 0) ? -index : index];
		n /= base;
	}
	if (negative)
		buff[i--] = '-';
	index = 0;
	while (buff[++i])
		new_buff[index++] = buff[i];
	new_buff[index] = 0;
}
