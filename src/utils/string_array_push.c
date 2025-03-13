/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array_push.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:30:44 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/13 22:33:45 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_array.h"

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

void	string_array_unshift(char ***arr, char *str)
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
		ft_memcpy(dup + 1, *arr, arr_len * sizeof(**arr));
	dup[0] = str;
	if (*arr)
		free(*arr);
	*arr = dup;
}
