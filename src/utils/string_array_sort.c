/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 23:05:28 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/15 14:49:30 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_array.h"

static int	cmp_alpha(char *a, char *b)
{
	while (*a && *b && *a == *b)
	{
		a++;
		b++;
	}
	return (*b - *a);
}

static int	get_index(char **arr, char *value, int (cmp)(char*, char*))
{
	int		index;

	index = 0;
	while (*arr)
		index += cmp(*(arr++), value) > 0;
	return (index);
}

int	*string_array_create_indexes(char **arr, int (cmp)(char*, char*))
{
	int		len;
	int		*indexes;
	int		i;

	len = string_array_len(arr);
	indexes = ft_calloc(len, sizeof(*indexes));
	if (!indexes)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		indexes[get_index(arr, arr[i], cmp)] = i;
		i++;
	}
	return (indexes);
}

void	string_array_sort(char **arr, int (cmp)(char*, char*))
{
	int		*indexes;
	char	**dup;
	int		len;
	int		i;

	indexes = string_array_create_indexes(arr, cmp);
	dup = string_array_dup_shallow(arr);
	len = string_array_len(arr);
	i = 0;
	while (i < len)
	{
		arr[i] = dup[indexes[i]];
		i++;
	}
	free(indexes);
	free(dup);
	return ;
}

void	string_array_sort_alpha(char **arr)
{
	string_array_sort(arr, cmp_alpha);
}
