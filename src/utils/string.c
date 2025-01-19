/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:21:40 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/19 22:24:22 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

static t_string_result	string_ensure_malloc(t_string *string)
{
	char	*new;

	if (!string->value)
	{
		string->value = ft_calloc(STRING_INITAL_LEN, 1);
		if (!string->value)
			return (STRING_ERROR);
		string->len = STRING_INITAL_LEN;
		return (STRING_SUCCESS);
	}
	if (string->value[string->len - 2])
	{
		new = ft_calloc(string->len * 2, 1);
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

void	string_free(t_string *string)
{
	if (!string->value)
		return ;
	free(string->value);
	string->value = NULL;
}
