/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:28:12 by jvoisard          #+#    #+#             */
/*   Updated: 2024/10/11 14:56:31 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_new;
	void	*content_new;

	if (!lst)
		return (0);
	content_new = f(lst->content);
	if (!content_new)
		return (0);
	lst_new = ft_lstnew(content_new);
	if (!lst_new)
	{
		del(content_new);
		return (0);
	}
	if (lst->next)
	{
		lst_new->next = ft_lstmap(lst->next, f, del);
		if (!lst_new->next)
		{
			del(lst_new->content);
			free(lst_new);
			return (0);
		}
	}
	return (lst_new);
}
