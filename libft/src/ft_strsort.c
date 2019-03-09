/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:33:04 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/21 14:45:58 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strsort(char *str)
{
	char	*s;
	char	*ptr;
	char	tmp;

	if (str == 0)
		return (0);
	s = str;
	while (*s)
	{
		ptr = s + 1;
		while (*ptr)
		{
			if (*ptr < *s)
			{
				tmp = *ptr;
				*ptr = *s;
				*s = tmp;
			}
			ptr++;
		}
		s++;
	}
	return (str);
}
