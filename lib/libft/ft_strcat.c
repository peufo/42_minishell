/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:15:31 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/17 12:03:44 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *a, char *b)
{
	int		len;
	char	*cat;
	char	*cursor;

	len = ft_strlen(a) + ft_strlen(b);
	cat = ft_calloc(len + 1, 1);
	cursor = cat;
	if (!cat)
		return (NULL);
	while (*a)
		*(cursor++) = *(a++);
	while (*b)
		*(cursor++) = *(b++);
	return (cat);
}
