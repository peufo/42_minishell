/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:51:11 by jvoisard          #+#    #+#             */
/*   Updated: 2024/10/08 16:33:13 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(str) + 1;
	dup = ft_calloc(len, sizeof(*dup));
	if (dup)
		ft_strlcpy(dup, str, len);
	return (dup);
}
