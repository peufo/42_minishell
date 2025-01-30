/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:20:48 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/30 12:21:00 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	type_or_func(char **s)
{
	int		i;
	int		j;
	int		int_num;
	char	number[256];

	i = 0;
	j = 0;
	if (!*s)
		return ;
	(void)int_num;
	(void)number;
	(void)i;
	(void)j;
}

void	get_macro(char *s)
{
	int	i;

	i = 0;
	type_or_func(&s);
	while (s[i])
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
			ft_putchar_fd(s[i++], 1);
		else
			i++;
	}
	ft_putchar_fd('\n', 1);
}
