/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:58:27 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/15 12:09:54 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	is_space(char c)
{
	return (c == ' '
		|| c == '\t'
		|| c == '\n'
		|| c == '\v'
		|| c == '\f'
		|| c == '\r');
}

int	ft_atoi(const char *str)
{
	int		n;
	short	sign;

	n = 0;
	sign = 1;
	if (!str)
		return (0);
	while (is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
		sign -= (*(str++) == '-') * 2;
	while (*str == '0')
		str++;
	while (ft_isdigit(*str))
		n = n * 10 + sign * (*(str++) - '0');
	return (n);
}
