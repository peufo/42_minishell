/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:05:56 by jvoisard          #+#    #+#             */
/*   Updated: 2024/10/08 16:32:14 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;

	p = s;
	if (n == 0)
		return ((void *)0);
	while (--n)
		if (*(p++) == (unsigned char)c)
			return ((void *)(p - 1));
	if (*p == (unsigned char)c)
		return ((void *)(p));
	return (0);
}
