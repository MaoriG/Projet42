/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:23:32 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/12 10:52:14 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstaddback(t_list **new_list, t_list *lst, void *(f)(void *))
{
	t_list	*new_e;
	t_list	*temp;

	new_e = malloc(sizeof(t_list));
	if (!new_e)
		return (NULL);
	new_e->content = f(lst->content);
	new_e->next = NULL;
	if (!*new_list)
		*new_list = new_e;
	else
	{
		temp = *new_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_e;
	}
	return (new_e);
}

t_list	*ft_lstmap(t_list *lst, void *(f)(void *), void (*del)(void *))
{
	t_list	*new;

	if (!lst || !f)
		return (NULL);
	new = NULL;
	while (lst)
	{
		if (!ft_lstaddback(&new, lst, f) && del)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (new);
}
