/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:20:15 by jvoisard          #+#    #+#             */
/*   Updated: 2024/10/11 10:48:18 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_empty_str(void)
{
	char	*str;

	str = malloc(1);
	if (!str)
		return (0);
	*str = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	str_len;

	if (!s)
		return (0);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_empty_str());
	if (len > (str_len - start))
		len = str_len - start;
	sub = ft_calloc(len + 1, sizeof(char));
	if (!sub)
		return (0);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}
