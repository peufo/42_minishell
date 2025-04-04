/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:17:20 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/05 00:11:20 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void *data, int (*get_status)(void *, void *))
{
	if (lst && get_status && get_status(data, lst->content) != 0)
		return ;
	if (lst && lst->next)
		ft_lstiter(lst->next, data, get_status);
}
