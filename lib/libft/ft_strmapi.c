/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 21:25:34 by jvoisard          #+#    #+#             */
/*   Updated: 2024/10/08 16:33:45 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len;
	char			*res;
	unsigned int	index;

	if (!s)
		return (0);
	len = ft_strlen(s);
	res = malloc(len + 1);
	if (!res)
		return (0);
	index = 0;
	while (index < len)
	{
		res[index] = f(index, s[index]);
		index++;
	}
	res[len] = '\0';
	return (res);
}
