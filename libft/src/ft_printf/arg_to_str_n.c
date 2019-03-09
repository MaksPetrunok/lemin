/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:34:39 by mpetruno          #+#    #+#             */
/*   Updated: 2018/10/23 14:04:42 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	arg_to_str_di(t_fmarg *arg, va_list *ap, char *buff)
{
	if (arg->flags & F_LLONG)
		ft_lltoa_base((long long)va_arg(*ap, long long), 10, 0, buff);
	else if (arg->flags & F_LONG)
		ft_lltoa_base((long)va_arg(*ap, long), 10, 0, buff);
	else if (arg->flags & F_INTMAX)
		ft_lltoa_base((signed long long)va_arg(*ap, intmax_t), 10, 0, buff);
	else if (arg->flags & F_SIZE_T)
		ft_lltoa_base((signed long int)va_arg(*ap, size_t), 10, 0, buff);
	else if (arg->flags & F_SHORT)
		ft_lltoa_base((short)va_arg(*ap, int), 10, 0, buff);
	else if (arg->flags & F_CHAR)
		ft_lltoa_base((signed char)va_arg(*ap, int), 10, 0, buff);
	else
		ft_lltoa_base(va_arg(*ap, int), 10, 0, buff);
}

void	arg_to_str_oux(t_fmarg *arg, va_list *ap, char *buff)
{
	unsigned long long	val;

	if (arg->flags & F_LLONG)
		val = (unsigned long long)va_arg(*ap, unsigned long long);
	else if (arg->flags & F_LONG)
		val = (unsigned long)va_arg(*ap, unsigned long);
	else if (arg->flags & F_SIZE_T)
		val = (size_t)va_arg(*ap, size_t);
	else if (arg->flags & F_INTMAX)
		val = (uintmax_t)va_arg(*ap, uintmax_t);
	else if (arg->flags & F_SHORT)
		val = (unsigned short)va_arg(*ap, int);
	else if (arg->flags & F_CHAR)
		val = (unsigned char)va_arg(*ap, int);
	else
		val = (unsigned int)va_arg(*ap, int);
	if (arg->type == 'o')
		ft_ulltoa_base(val, 8, 0, buff);
	else if (arg->type == 'u')
		ft_ulltoa_base(val, 10, 0, buff);
	else if (ft_strchr("pxX", arg->type))
		ft_ulltoa_base(val, 16, arg->type == 'X', buff);
	else if (arg->type == 'b')
		ft_ulltoa_base(val, 2, 0, buff);
}

void	arg_to_str_f(t_fmarg *arg, va_list *ap, char *buff)
{
	ft_dtoa((double)va_arg(*ap, double),
		!(arg->flags & F_PREC) ? 6 : arg->precision, buff);
}
