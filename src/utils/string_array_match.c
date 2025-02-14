/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array_match.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:22:06 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/14 11:24:22 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_array.h"

bool	string_match(char *pattern, char *str)
{
	return (!ft_strcmp(pattern, str));
}

bool	string_match_start_with(char *pattern, char *str)
{
	while (*pattern && *str)
	{
		if (*pattern != *str)
			return (false);
		str++;
		pattern++;
	}
	if (*pattern && !*str)
		return (false);
	return (true);
}
