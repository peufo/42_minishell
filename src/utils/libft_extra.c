/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:20:44 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/09 06:37:45 by dyodlm           ###   ########.fr       */
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

void	init_utils(t_utils **u)
{
	*u = malloc(sizeof(t_utils));
	if (!(*u))
		return (throw_error("malloc in :", __FILE__, __LINE__));
	(*u)->i = 0;
	(*u)->j = 0;
	(*u)->k = 0;
	(*u)->x = 0;
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
