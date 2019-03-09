/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 20:40:18 by mpetruno          #+#    #+#             */
/*   Updated: 2019/01/04 15:49:52 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstins(t_list **alst, t_list *new, int (*sort)(void *, void*))
{
	t_list	*iter;
	t_list	*prev;

	if (!alst || !new || !sort)
		return ;
	if (!(*alst))
	{
		ft_lstadd(alst, new);
		return ;
	}
	iter = *alst;
	prev = 0;
	while (iter && sort(new->content, iter->content) > 0)
	{
		prev = iter;
		iter = iter->next;
	}
	new->next = iter;
	if (prev == 0)
		*alst = new;
	else
		prev->next = new;
}
