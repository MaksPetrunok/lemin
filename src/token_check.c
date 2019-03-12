/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 13:34:08 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/12 13:34:09 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	is_room(const char *str)
{
	char	*x;
	char	*y;

	if (*str == 'L' || *str == ' ')
		return (0);
	else if ((x = ft_strchr(str, ' ')) == NULL ||
			(y = ft_strchr(x + 1, ' ')) == NULL)
		return (0);
	else if (*(x + 1) == '\0' || *(y + 1) == '\0')
		return (0);
	x += (*(x + 1) == '-' || *(x + 1) == '+') ? 2 : 1;
	y += (*(y + 1) == '-' || *(y + 1) == '+') ? 2 : 1;
	while (*x && *x != ' ')
	{
		if (!ft_isdigit(*x++))
			return (0);
	}
	while (*y)
	{
		if (!ft_isdigit(*y++))
			return (0);
	}
	return (1);
}

int	is_link(const char *str)
{
	char	*delim;

	delim = ft_strchr(str, '-');
	if (!delim)
		return (0);
	if (ft_strchr(str, ' '))
		return (0);
	if (*str == '-')
		return (0);
	if (*(delim + 1) == '\0' || *(delim + 1) == '-')
		return (0);
	return (1);
}
