/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:05:13 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/22 17:06:19 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_array.h"

int	string_array_len(char **arr)
{
	int	index;

	index = 0;
	while (arr[index])
		index++;
	return (index + 1);
}

void	string_array_free(char ***arr)
{
	char	**cursor;

	if (!*arr)
		return ;
	cursor = *arr;
	while (*cursor)
		free(*(cursor++));
	free(*arr);
	*arr = NULL;
}

char	**string_array_dup(char **arr)
{
	char	**dup;
	int		i;

	if (!arr)
		return (NULL);
	dup = ft_calloc(string_array_len(arr) + 1, sizeof(*arr));
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

void	string_array_push(char ***arr, char *str)
{
	char	**dup;
	int		i;

	if (!str)
		return ;
	dup = ft_calloc(string_array_len(*arr) + 2, sizeof(**arr));
	if (!dup)
		return ;
	i = 0;
	while ((*arr)[i])
	{
		dup[i] = (*arr)[i];
		i++;
	}
	dup[i] = str;
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
	*arr = NULL;
}
