/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 01:06:44 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/17 14:36:01 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *a, const char *b)
{
	char	*str;
	size_t	len;

	if (!a || !b)
		return (0);
	len = ft_strlen(a) + ft_strlen(b) + 1;
	str = ft_calloc(len, sizeof(*str));
	if (!str)
		return (str);
	ft_strlcat(str, a, len);
	ft_strlcat(str, b, len);
	return (str);
}
