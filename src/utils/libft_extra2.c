/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extra2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:00:09 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/05 10:03:12 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchrstr(const char *str, char *to_find)
{
	char	*cursor;
	size_t	j;
	size_t	len;

	len = ft_strlen(to_find);
	cursor = (char *)str;
	while (cursor && *cursor)
	{
		j = 0;
		while (cursor[j] == to_find[j])
			j++;
		if (j >= len)
			return (cursor);
		cursor++;
	}
	return (NULL);
}
