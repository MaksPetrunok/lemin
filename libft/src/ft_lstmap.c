/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 20:55:03 by mpetruno          #+#    #+#             */
/*   Updated: 2018/06/10 21:21:21 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	clear_memory(t_list *l)
{
	t_list *tmp;

	tmp = l;
	while (l)
	{
		tmp = l->next;
		free(l->content);
		free((void *)l);
		l = tmp;
	}
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*res;
	t_list	*tmp;

	res = f(lst);
	if (res == 0)
		return (0);
	tmp = res;
	lst = lst->next;
	while (lst)
	{
		tmp->next = f(lst);
		tmp = tmp->next;
		if (tmp == 0)
		{
			clear_memory(res);
			return (0);
		}
		lst = lst->next;
	}
	return (res);
}
