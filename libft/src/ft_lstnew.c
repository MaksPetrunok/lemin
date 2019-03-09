/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 18:58:35 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/13 16:27:37 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*res;

	if ((res = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	res->next = 0;
	res->content_size = content_size;
	if (content == NULL)
	{
		res->content = NULL;
		res->content_size = 0;
	}
	else if ((res->content = malloc(content_size)) == NULL)
	{
		free((void *)res);
		return (0);
	}
	else
		res->content = ft_memcpy(res->content, content, content_size);
	return (res);
}
