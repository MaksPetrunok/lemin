/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 12:35:34 by mpetruno          #+#    #+#             */
/*   Updated: 2018/10/23 13:34:53 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	initialize_fmarg(t_fmarg *arg)
{
	arg->flags = 0;
	arg->width = 0;
	arg->precision = -1;
	arg->type = '\0';
}

static void	process_arg(char **str, va_list *ap, t_outbuff *buffer)
{
	t_fmarg	arg;

	*str = *str + 1;
	initialize_fmarg(&arg);
	parse_flags(str, &arg, ap);
	print_arg(&arg, ap, buffer);
}

int			ft_dprintf(int fd, const char *fmt, ...)
{
	va_list		ap;
	char		*arg;
	t_outbuff	buffer;

	if (fmt == 0 || fd < 0)
		return ((fd < 0) ? -1 : 0);
	initialize_output_buff(&buffer, fd);
	va_start(ap, fmt);
	while ((arg = ft_strchr(fmt, '%')))
	{
		if (fmt != arg)
			append(&buffer, fmt, arg - fmt);
		process_arg(&arg, &ap, &buffer);
		fmt = arg;
	}
	append(&buffer, fmt, -1);
	flush(&buffer);
	va_end(ap);
	return (buffer.count);
}

int			ft_printf(const char *fmt, ...)
{
	va_list		ap;
	char		*arg;
	t_outbuff	buffer;

	if (fmt == 0)
		return (0);
	initialize_output_buff(&buffer, 1);
	va_start(ap, fmt);
	while ((arg = ft_strchr(fmt, '%')))
	{
		if (fmt != arg)
			append(&buffer, fmt, arg - fmt);
		process_arg(&arg, &ap, &buffer);
		fmt = arg;
	}
	append(&buffer, fmt, -1);
	flush(&buffer);
	va_end(ap);
	return (buffer.count);
}
