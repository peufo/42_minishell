/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array_find.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 21:24:04 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/22 16:55:27 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_array.h"

static bool	match_start_with(char *pattern, char *str)
{
	while (*pattern && *str)
	{
		if (*pattern != *str)
			return (false);
		str++;
		pattern++;
	}
	if (*pattern && !*str)
		return (false);
	return (true);
}

char	**string_array_find(
	char **arr,
	char *pattern,
	bool (*match)(char *, char *)
)
{
	while (*arr)
	{
		if (match(pattern, *arr))
			return (arr);
		arr++;
	}
	return (NULL);
}

char	**string_array_find_start_with(char **arr, char *pattern)
{
	return (string_array_find(arr, pattern, match_start_with));
}
