/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 15:31:23 by mpetruno          #+#    #+#             */
/*   Updated: 2018/10/23 14:05:14 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_c(t_fmarg *a, char *s, int len, t_outbuff *buffer)
{
	char	fill;
	int		n;

	if (*s == '\0')
		a->precision = -1;
	fill = (a->flags & F_ZERO) ? '0' : ' ';
	if (!(a->flags & F_LEFT) && (n = (a->width - (MAX(a->precision, len)))) > 0)
		appendchr(buffer, fill, n);
	if ((n = (a->precision - len)) > 0 && a->width != 0)
		appendchr(buffer, ' ', n);
	appendnchr(buffer, s, len);
	if (a->flags & F_LEFT && (n = (a->width - (MAX(a->precision, len)))) > 0)
		appendchr(buffer, ' ', n);
}

void	print_s(t_fmarg *a, char *s, int len, t_outbuff *buffer)
{
	char	fill;
	int		n;

	if (s == 0)
	{
		s = "(null)";
		len = ft_strlen(s);
		a->precision = (a->flags & F_PREC) ? 0 : a->precision;
		a->flags = (a->flags & F_LONG) ? a->flags ^ (int)F_LONG : a->flags;
		a->flags = (a->flags & F_PREC) ? a->flags ^ (int)F_PREC : a->flags;
	}
	len = (a->precision >= 0 && a->precision < len) ?
		a->precision : len;
	a->precision = (*s == 0) ? 0 : a->precision;
	fill = (a->flags & F_ZERO) ? '0' : ' ';
	if (!(a->flags & F_LEFT) && (n = (a->width - len)) > 0)
		appendchr(buffer, fill, n);
	if (*s == '\0' && (n = (a->precision - len)) > 0 && a->width != 0)
		appendchr(buffer, ' ', n);
	if (len > 0)
		append(buffer, s, len);
	if (a->flags & F_LEFT && (n = (a->width - (MAX(a->precision, len)))) > 0)
		appendchr(buffer, ' ', n);
	if (a->flags & F_LONG)
		free((void *)s);
}
