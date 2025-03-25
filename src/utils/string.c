/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:21:40 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/25 13:40:43 by jvoisard         ###   ########.fr       */
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

char	*string_push_char(t_string *string, char c)
{
	if (string_ensure_malloc(string, 1))
		return (NULL);
	ft_strlcat(string->value, (char []){c, '\0'}, string->len);
	return (string->value + ft_strlen(string->value));
}

char	*string_push_str(t_string *string, char *str)
{
	if (!str)
		return (NULL);
	if (string_ensure_malloc(string, ft_strlen(str)))
		return (NULL);
	ft_strlcat(string->value, str, string->len);
	return (string->value + ft_strlen(string->value));
}

t_string_result	string_replace(
	t_string *string,
	char *start,
	char *end,
	char *with)
{
	int		index_start;
	int		index_end;
	char	*w;
	char	*r;

	if (!with)
		return (STRING_ERROR);
	index_start = start - string->value;
	index_end = end - string->value;
	if (string_ensure_malloc(string, (ft_strlen(with) - (end - start))))
		return (STRING_ERROR);
	start = string->value + index_start;
	end = string->value + index_end;
	r = end;
	while (*r)
		r++;
	w = r + ft_strlen(with) - (end - start);
	while (r > start)
		*(w--) = *(r--);
	w = start;
	r = with;
	while (*r)
		*(w++) = *(r++);
	return (STRING_SUCCESS);
}

void	string_free(t_string *string)
{
	if (!string || !string->value)
		return ;
	free(string->value);
	string->value = NULL;
}
