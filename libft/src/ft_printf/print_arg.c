/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:34:39 by mpetruno          #+#    #+#             */
/*   Updated: 2018/10/23 13:51:24 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_string(t_fmarg *a, char *s, int len, t_outbuff *buffer)
{
	if (a->type == 'd' || a->type == 'i')
		print_di(a, s, len, buffer);
	else if (a->type == 'o')
		print_o(a, s, len, buffer);
	else if (a->type == 'f' || a->type == 'F')
		print_f(a, s, len, buffer);
	else if (ft_strchr("xpXb", a->type))
		print_x(a, s, len, buffer);
	else if (ft_strchr("u", a->type))
		print_u(a, s, len, buffer);
	else if (ft_strchr("c%", a->type))
		print_c(a, s, MAX(1, len), buffer);
	else if (ft_strchr("s", a->type))
		print_s(a, s, len, buffer);
}

void		print_arg(t_fmarg *arg, va_list *ap, t_outbuff *buffer)
{
	char	*str;
	char	buff[NTOA_BUFF_SIZE];

	if (arg->type == '\0')
		return ;
	str = "%";
	if (arg->type == 'd' || arg->type == 'i')
		arg_to_str_di(arg, ap, (str = buff));
	else if (ft_strchr("ouxXbp", arg->type))
		arg_to_str_oux(arg, ap, str = buff);
	else if (arg->type == 'f' || arg->type == 'F')
		arg_to_str_f(arg, ap, str = buff);
	else if (arg->type == 'c')
		arg_to_str_c(arg, ap, str = buff);
	else if (arg->type == 's')
		arg_to_str_s(arg, ap, &str);
	else if (ft_strchr(TYPES, arg->type) == 0)
	{
		buff[0] = arg->type;
		buff[1] = '\0';
		arg->type = 'c';
		str = buff;
	}
	print_string(arg, str, (str) ? ft_strlen(str) : 0, buffer);
}
