/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:20:44 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/01 11:37:07 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_include(char *str, char c)
{
	while (*str)
		if (*(str++) == c)
			return (true);
	return (false);
}

bool	ft_startwith(char *str, char *start)
{
	while (*start && *str)
		if (*(start++) != *(str++))
			return (false);
	if (*start)
		return (false);
	return (true);
}

int	ft_isop(char *str)
{
	int			i;
	static char	*ops[] = {
		"&&",
		"||",
		"<<",
		">>",
		"<",
		">",
		"|",
		"abc",
		"efg"
	};

	i = 0;
	while (ft_strncmp(ops[i], str, ft_strlen(str)) && i < 8)
		i++;
	if (i >= 6)
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

char	*ft_strrchrstr(const char *str, char *to_find)
{
	char	*cursor;
	char	*res;
	size_t	j;
	size_t	len;

	res = NULL;
	len = ft_strlen(to_find);
	cursor = (char *)str;
	while (cursor && *cursor)
	{
		j = 0;
		while (cursor[j] == to_find[j])
			j++;
		if (j >= len)
			res = cursor;
		cursor++;
	}
	return (res);
}
