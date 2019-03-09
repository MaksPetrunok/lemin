/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nums.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:34:39 by mpetruno          #+#    #+#             */
/*   Updated: 2018/10/23 13:35:49 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_f(t_fmarg *a, char *s, int len, t_outbuff *buffer)
{
	char	fill;
	int		n;

	fill = (a->flags & F_ZERO) ? '0' : ' ';
	a->width -= (*s == '-' || (a->flags & (F_PLUS | F_SPACE)));
	len -= (*s == '-');
	if (!(a->flags & F_LEFT) && fill == ' '
		&& (n = (a->width - (MAX(a->precision, len)))) > 0)
		appendchr(buffer, ' ', n);
	if (*s == '-')
		appendchr(buffer, *s++, 1);
	else if (a->flags & F_PLUS)
		appendchr(buffer, '+', 1);
	else if (a->flags & F_SPACE)
		appendchr(buffer, ' ', 1);
	if (!(a->flags & F_LEFT) && fill == '0'
		&& (n = (a->width - (MAX(a->precision, len)))) > 0)
		appendchr(buffer, '0', n);
	if ((n = (a->precision - len)) > 0)
		appendchr(buffer, '0', n);
	append(buffer, s, len);
	if (a->flags & F_LEFT && (n = (a->width - (MAX(a->precision, len)))) > 0)
		appendchr(buffer, ' ', n);
}

void	print_di(t_fmarg *a, char *s, int len, t_outbuff *buffer)
{
	char	fill;
	int		n;

	len -= (*s == '-');
	len = (a->precision == 0 && *s == '0') ? 0 : len;
	fill = ((a->flags & F_ZERO) && a->precision < 0) ? '0' : ' ';
	a->width -= (*s == '-' || (a->flags & (F_PLUS | F_SPACE)));
	if (!(a->flags & F_LEFT) && fill == ' '
		&& (n = (a->width - (MAX(a->precision, len)))) > 0)
		appendchr(buffer, ' ', n);
	if (*s == '-')
		appendchr(buffer, *s++, 1);
	else if (a->flags & F_PLUS)
		appendchr(buffer, '+', 1);
	else if (a->flags & F_SPACE)
		appendchr(buffer, ' ', 1);
	if (!(a->flags & F_LEFT) && fill == '0'
		&& (n = (a->width - (MAX(a->precision, len)))) > 0)
		appendchr(buffer, '0', n);
	if ((n = (a->precision - len)) > 0)
		appendchr(buffer, '0', n);
	append(buffer, s, len);
	if (a->flags & F_LEFT && (n = (a->width - (MAX(a->precision, len)))) > 0)
		appendchr(buffer, ' ', n);
}

void	print_u(t_fmarg *a, char *s, int len, t_outbuff *buffer)
{
	char	fill;
	int		n;

	len = (a->precision == 0 && *s == '0') ? 0 : len;
	fill = (a->flags & F_ZERO) ? '0' : ' ';
	if (!(a->flags & F_LEFT) && (n = (a->width - (MAX(a->precision, len)))) > 0)
		appendchr(buffer, (a->precision < 0) ? fill : ' ', n);
	if ((n = (a->precision - len)) > 0)
		appendchr(buffer, '0', n);
	append(buffer, s, len);
	if (a->flags & F_LEFT && (n = (a->width - (MAX(a->precision, len)))) > 0)
		appendchr(buffer, ' ', n);
}

void	print_o(t_fmarg *a, char *s, int len, t_outbuff *buffer)
{
	char	fill;
	int		n;

	len = (a->precision == 0 && !(a->flags & F_HASH)) ? 0 : len;
	fill = ((a->flags & F_ZERO) && a->precision < 0) ? '0' : ' ';
	a->width -= ((a->flags & F_HASH));
	a->precision -= ((a->flags & F_HASH));
	if (!(a->flags & F_LEFT) && (n = (a->width - (MAX(a->precision, len)))) > 0)
		appendchr(buffer, fill, n);
	if (a->flags & F_HASH && *s != '0')
		appendchr(buffer, '0', 1);
	if ((n = (a->precision - len)) > 0)
		appendchr(buffer, '0', n);
	append(buffer, s, len);
	if (a->flags & F_LEFT && (n = (a->width - (MAX(a->precision, len)))) > 0)
		appendchr(buffer, ' ', n);
}

void	print_x(t_fmarg *a, char *s, int len, t_outbuff *buffer)
{
	char	fill;
	int		n;

	len = (a->precision == 0) ? 0 : len;
	fill = ((a->flags & F_ZERO) && a->precision < 0) ? '0' : ' ';
	a->width -= (a->flags & F_HASH) * 2;
	if (!(a->flags & F_LEFT) && fill == ' ' &&
			(n = (a->width - (MAX(a->precision, len)))) > 0)
		appendchr(buffer, fill, n);
	if (a->flags & F_HASH && (*s != '0' || a->type == 'p'))
		append(buffer, (a->type == 'X') ? "0X" : "0x", 2);
	if (!(a->flags & F_LEFT) && fill == '0' &&
			(n = (a->width - (MAX(a->precision, len)))) > 0)
		appendchr(buffer, fill, n);
	if ((n = (a->precision - len)) > 0)
		appendchr(buffer, '0', n);
	append(buffer, s, len);
	if (a->flags & F_LEFT && (n = (a->width - (MAX(a->precision, len)))) > 0)
		appendchr(buffer, ' ', n);
}
