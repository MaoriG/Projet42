/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:07:53 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/11 18:39:25 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (*lst && lst && del)
	{
		while (*lst != NULL)
		{
			temp = *lst;
			*lst = (*lst)->next;
			del(temp-> content);
			free (temp);
		}
		*lst = temp;
		*lst = NULL;
	}
}
