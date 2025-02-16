/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:29:28 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/16 16:39:46 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcut(char *start, char *end)
{
	char	*dup;
	char	*cursor;

	dup = ft_calloc(end - start + 1, 1);
	cursor = dup;
	if (!dup)
		return (NULL);
	while (start < end)
		*(cursor++) = *(start++);
	*cursor = '\0';
	return (dup);
}
