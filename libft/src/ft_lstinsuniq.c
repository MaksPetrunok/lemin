/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsuniq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 20:40:18 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 19:13:48 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	insert(t_list *new, t_list **alst, t_list **iter, t_list **prev)
{
	new->next = *iter;
	if (*prev == 0)
		*alst = new;
	else
		(*prev)->next = new;
}

int			ft_lstinsuniq(t_list **alst, t_list *new,
										int (*sort)(void *, void*))
{
	t_list	*iter;
	t_list	*prev;
	int		is_equal;

	if (!alst || !new || !sort)
		return (0);
	if (!(*alst))
	{
		ft_lstadd(alst, new);
		return (1);
	}
	iter = *alst;
	prev = 0;
	while (iter && (is_equal = sort(new->content, iter->content)) > 0)
	{
		prev = iter;
		iter = iter->next;
	}
	if (is_equal == 0)
		return (0);
	insert(new, alst, &iter, &prev);
	return (1);
}
