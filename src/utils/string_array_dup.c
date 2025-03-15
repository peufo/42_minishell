/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array_dup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 23:16:52 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/14 23:19:04 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_array.h"

char	**string_array_dup(char **arr)
{
	char	**dup;
	int		arr_len;
	int		i;

	if (!arr)
		return (NULL);
	arr_len = string_array_len(arr);
	dup = ft_calloc(arr_len + 1, sizeof(*arr));
	if (!dup)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		dup[i] = ft_strdup(arr[i]);
		if (!dup[i])
			return (string_array_free(&dup), NULL);
		i++;
	}
	return (dup);
}

char	**string_array_dup_shallow(char **arr)
{
	char	**dup;
	int		arr_len;
	int		i;
	
	if (!arr)
		return (NULL);
	arr_len = string_array_len(arr);
	dup = ft_calloc(arr_len + 1, sizeof(*arr));
	if (!dup)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		dup[i] = arr[i];
		i++;
	}
	return (dup);
}
