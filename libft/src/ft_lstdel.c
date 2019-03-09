/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 20:07:51 by mpetruno          #+#    #+#             */
/*   Updated: 2018/06/18 18:44:10 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;

	if (!alst || !del)
		return ;
	while (*alst != 0)
	{
		tmp = (*alst)->next;
		del((*alst)->content, (*alst)->content_size);
		free((void *)(*alst));
		*alst = tmp;
	}
	*alst = 0;
}
