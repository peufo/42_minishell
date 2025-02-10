/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:20:44 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/10 15:05:28 by jvoisard         ###   ########.fr       */
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
