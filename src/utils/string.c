/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:21:40 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/15 19:53:21 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

static t_string_result	string_ensure_malloc(t_string *string)
{
	char	*new;

	if (!string->value)
	{
		string->value = malloc(STRING_INITAL_LEN);
		if (!string->value)
			return (STRING_ERROR);
		ft_memset(string->value, 0, STRING_INITAL_LEN);
		string->len = STRING_INITAL_LEN;
		return (STRING_SUCCESS);
	}
	if (string->value[string->len - 2])
	{
		new = malloc(string->len * 2);
		if (!new)
			return (free(string->value), string->value = NULL, STRING_ERROR);
		ft_memmove(new, string->value, string->len);
		free(string->value);
		string->value = new;
		string->len *= 2;
	}
	return (STRING_SUCCESS);
}

t_string_result	string_push(t_string *string, char c)
{
	if (string_ensure_malloc(string))
		return (STRING_ERROR);
	ft_strlcat(string->value, (char []){c, '\0'}, string->len);
	return (STRING_SUCCESS);
}
