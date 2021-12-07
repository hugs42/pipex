/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 11:36:23 by hugsbord          #+#    #+#             */
/*   Updated: 2021/06/28 16:59:03 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*elem;
	t_list	*begin;

	if (!lst)
		return (NULL);
	elem = ft_lstnew(f(lst->content));
	if (!(elem))
		return (NULL);
	lst = lst->next;
	begin = elem;
	while (lst)
	{
		elem->next = ft_lstnew(f(lst->content));
		if (!(elem->next))
		{
			ft_lstclear(&begin, del);
			return (NULL);
		}
		elem = elem->next;
		lst = lst->next;
	}
	return (begin);
}
