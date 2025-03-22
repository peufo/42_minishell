/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:10:39 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/19 11:21:14 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_flag(char *str)
{
	if (!*str || *str != '-')
		return (false);
	str++;
	if (*str != 'n')
		return (false);
	while (*str)
		if (*str++ != 'n')
			return (false);
	return (true);
}

int	builtin_echo(t_ast *node)
{
	char	**args;
	bool	new_line;

	new_line = true;
	args = node->tokens + 1;
	while (args && *args)
	{
		if (!is_flag(*args))
			break ;
		args++;
		new_line = false;
	}
	while (*args)
	{
		ft_putstr(*args);
		if (args[1])
			ft_putstr(" ");
		args++;
	}
	if (new_line)
		ft_putstr("\n");
	return (0);
}
