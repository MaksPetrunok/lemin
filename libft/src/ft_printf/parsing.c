/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:32:12 by mpetruno          #+#    #+#             */
/*   Updated: 2018/10/23 14:18:25 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	parse_length(char **str, t_fmarg *arg)
{
	int	lenmod;

	lenmod = 0;
	if (**str == 'h')
		lenmod |= (*(*str + 1) == 'h') ? F_CHAR : F_SHORT;
	else if (**str == 'l')
		lenmod |= (*(*str + 1) == 'l') ? F_LLONG : F_LONG;
	else if (**str == 'j')
		lenmod |= F_INTMAX;
	else if (**str == 'z')
		lenmod |= F_SIZE_T;
	else
		return (0);
	*str += ((lenmod & (F_CHAR | F_LLONG)) > 0) * 2 +
		((lenmod & (F_SHORT | F_LONG | F_INTMAX | F_SIZE_T)) > 0);
	arg->flags |= lenmod;
	return (1);
}

static char	parse_type(char **str, t_fmarg *arg)
{
	if (**str == '\0' || ft_strchr(TYPES, **str) == 0)
		return (0);
	else
		arg->type = **str;
	*str = *str + 1;
	if (ft_strchr("DOUCS", arg->type) != 0)
	{
		arg->type = ft_tolower(arg->type);
		arg->flags |= F_LONG;
	}
	if (arg->type == 'p')
		arg->flags |= F_HASH | F_LLONG;
	return (1);
}

static char	parse_num(char **s, int *n, va_list *ap)
{
	if (**s == '*')
	{
		*n = va_arg(*ap, int);
		(*s)++;
	}
	else
	{
		*n = ft_atoi(*s);
		while (**s >= '0' && **s <= '9')
			(*s)++;
	}
	return (1);
}

static char	parse_fl(char **s, t_fmarg *arg)
{
	int	tmp;

	if (**s == '#')
		arg->flags |= F_HASH;
	else if (**s == '0')
		arg->flags |= F_ZERO;
	else if (**s == '-')
		arg->flags |= F_LEFT;
	else if (**s == ' ')
		arg->flags |= F_SPACE;
	else if (**s == '+')
		arg->flags |= F_PLUS;
	if ((**s == '0' || **s == '-') && *(*s + 1) >= '0' && *(*s + 1) <= '9')
	{
		(*s)++;
		parse_num(s, &tmp, 0);
		if (tmp > 0)
			arg->width = tmp;
		else
			arg->flags &= (arg->flags & F_ZERO) ? ~F_ZERO : ~(unsigned long)0;
	}
	else
		(*s)++;
	return (1);
}

void		parse_flags(char **str, t_fmarg *arg, va_list *ap)
{
	char	cont;

	while (**str && arg->type == 0)
	{
		cont = 0;
		if (**str == '.')
		{
			(*str)++;
			cont = parse_num(str, &(arg->precision), ap);
		}
		else if ((**str >= '1' && **str <= '9') || **str == '*')
			cont = parse_num(str, &(arg->width), ap);
		else if (ft_strchr(FLAGS, **str) != 0)
			cont = parse_fl(str, arg);
		else
			cont = parse_length(str, arg);
		if (parse_type(str, arg) || !cont)
			break ;
	}
	if (arg->type == '\0' && **str)
		arg->type = *(*str)++;
	arg->flags |= (arg->width < 0) ? F_LEFT : 0;
	arg->width = ABS(arg->width);
	arg->flags |= (arg->precision >= 0) ? F_PREC : 0;
}
