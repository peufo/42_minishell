/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array_slice.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:23:03 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/23 17:50:27 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_array.h"

char	**string_array_slice(char **from, char **to)
{
	int		len;
	char	**slice;
	int		i;

	if (!to)
	{
		to = from;
		while (*to)
			to++;
	}
	len = to - from;
	if (len <= 0)
		return (NULL);
	slice = ft_calloc(len + 1, sizeof(*slice));
	if (!slice)
		return (NULL);
	i = 0;
	while (from < to)
	{
		slice[i] = ft_strdup(*(from++));
		if (!slice[i])
			return (string_array_free(&slice), NULL);
		i++;
	}
	return (slice);
}
