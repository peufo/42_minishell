/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array_join.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:33:28 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/15 12:47:28 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_array.h"

char	*string_array_join(char **arr, char *separator)
{
	t_string	join;

	join.value = NULL;
	if (!arr)
		return (NULL);
	if (*arr)
		string_push_str(&join, *(arr++));
	while (*arr)
	{
		string_push_str(&join, separator);
		string_push_str(&join, *(arr++));
	}
	return (join.value);
}
