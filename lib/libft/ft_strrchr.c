/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:01:10 by jvoisard          #+#    #+#             */
/*   Updated: 2024/10/08 16:33:55 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*s_origin;

	s_origin = s;
	while (*s++)
		;
	while (s > s_origin)
		if (*(--s) == (unsigned char)c)
			return ((char *)(s));
	return ((void *)0);
}
