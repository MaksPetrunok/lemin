/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:47:06 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/21 15:00:26 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strarr_sort(char **arr, int size)
{
	char	**a;
	char	**ptr;
	char	*tmp;

	if (arr == 0)
		return (0);
	a = arr;
	while (*a && a - arr < size)
	{
		ptr = a + 1;
		while (ptr && ptr - arr < size)
		{
			if (ft_strcmp(*ptr, *a) < 0)
			{
				tmp = *ptr;
				*ptr = *a;
				*a = tmp;
			}
			ptr++;
		}
		a++;
	}
	return (arr);
}
