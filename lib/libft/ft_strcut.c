/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:29:28 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/25 16:50:01 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcut(char *start, char *end)
{
	char	*dup;
	char	*cursor;

	if (!end)
	{
		end = start;
		while (*end)
			end++;
	}
	dup = ft_calloc(end - start + 1, 1);
	cursor = dup;
	if (!dup)
		return (NULL);
	while (start < end)
		*(cursor++) = *(start++);
	*cursor = '\0';
	return (dup);
}
