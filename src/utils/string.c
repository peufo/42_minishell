/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:21:40 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/04 22:13:34 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

static t_string_result	string_ensure_malloc(
	t_string *string,
	unsigned int needed_space
)
{
	char	*new;

	if (!string->value)
	{
		string->value = ft_calloc(STRING_INITAL_LEN, 1);
		if (!string->value)
			return (STRING_ERROR);
		string->len = STRING_INITAL_LEN;
	}
	while (
		(needed_space > string->len)
		|| (string->value[string->len - needed_space - 1])
	)
	{
		new = ft_calloc(string->len * 2, 1);
		if (!new)
			return (string_free(string), STRING_ERROR);
		ft_memmove(new, string->value, string->len);
		free(string->value);
		string->value = new;
		string->len *= 2;
	}
	return (STRING_SUCCESS);
}

t_string_result	string_push_char(t_string *string, char c)
{
	if (string_ensure_malloc(string, 1))
		return (STRING_ERROR);
	ft_strlcat(string->value, (char []){c, '\0'}, string->len);
	return (STRING_SUCCESS);
}

t_string_result	string_push_str(t_string *string, char *str)
{
	if (string_ensure_malloc(string, ft_strlen(str)))
		return (STRING_ERROR);
	ft_strlcat(string->value, str, string->len);
	return (STRING_SUCCESS);
}

void	string_free(t_string *string)
{
	if (!string || !string->value)
		return ;
	free(string->value);
	string->value = NULL;
}
