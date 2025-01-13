/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:07:30 by jvoisard          #+#    #+#             */
/*   Updated: 2024/10/08 19:01:11 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	size_t	i;

	if (!*find)
		return ((char *)str);
	if (str && !*str)
		return (0);
	while (len)
	{
		i = 0;
		while (str[i] && find[i] && str[i] == find[i])
		{
			if (!find[i + 1] && i < len)
				return ((char *)str);
			i++;
		}
		if (*str)
			str++;
		len--;
	}
	return (0);
}
