/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:23:32 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/11 19:12:34 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(f)(void *), void (*del)(void *))
{
    t_list *new;
    t_list *new_e;
    t_list *temp;

    if (!lst || !f)
        return (NULL);

    new = NULL;
    while (lst)
    {
        new_e = malloc(sizeof(t_list));
        if (!new_e)
        {
            if (del)
                ft_lstclear(&new, del);
            return (NULL);
        }
        new_e->content = f(lst->content);
        new_e->next = NULL;
        if (!new)
            new = new_e;
        else
        {
            temp = new;
            while (temp->next)
                temp = temp->next;
            temp->next = new_e;
        }
        lst = lst->next;
    }
    return (new);
}
