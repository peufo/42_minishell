/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:59:13 by jvoisard          #+#    #+#             */
/*   Updated: 2024/10/08 16:32:30 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*_dst;
	char	*_src;

	if (n == 0 || dst == src)
		return (dst);
	_src = (char *)src;
	_dst = (char *)dst;
	while (n--)
		*(_dst++) = *(_src++);
	return (dst);
}
