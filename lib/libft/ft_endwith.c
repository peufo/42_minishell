/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endwith.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:57:28 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/14 20:10:30 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_endwith(char *str, char *end)
{
	size_t	end_len;

	end_len = ft_strlen(end);
	if (ft_strlen(str) < end_len)
		return (0);
	while (*str)
		str++;
	str -= end_len;
	while (*str && *end)
		if (*(str++) != *(end++))
			return (0);
	return (1);
}
