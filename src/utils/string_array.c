/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:05:13 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/15 10:57:08 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_array.h"
#include <stdio.h>

int	string_array_len(char **arr)
{
	int	len;

	len = 0;
	if (!arr)
		return (0);
	while (arr[len])
		len++;
	return (len);
}

void	string_array_free(char ***arr)
{
	char	**cursor;

	if (!*arr)
		return ;
	cursor = *arr;
	while (*cursor)
	{
		free(*cursor);
		*cursor = NULL;
		cursor++;
	}
	free(*arr);
	*arr = NULL;
}

void	string_array_push(char ***arr, char *str)
{
	char	**dup;
	int		arr_len;

	if (!str)
		return ;
	arr_len = string_array_len(*arr);
	dup = ft_calloc(arr_len + 2, sizeof(**arr));
	if (!dup)
		return ;
	if (*arr)
		ft_memcpy(dup, *arr, arr_len * sizeof(**arr));
	dup[arr_len] = str;
	if (*arr)
		free(*arr);
	*arr = dup;
}

void	string_array_delete(char **arr, char *str)
{
	if (!str)
		return ;
	while (*arr && *arr != str)
		arr++;
	if (*arr != str)
		return ;
	while (*(arr + 1))
	{
		*arr = *(arr + 1);
		arr++;
	}
	free(str);
	*(arr) = NULL;
}
