/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:10:39 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/22 19:54:40 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_flag(char *str)
{
	if (!*str || *str != '-')
		return (false);
	str++;
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
	args = node->args + 1;
	while (args && *args)
	{
		if (!is_flag(*args))
			break ;
		args++;
		new_line = false;
	}
	while (*args)
	{
		ft_putstr_fd(*args, node->pipe.out);
		if (args[1])
			ft_putstr_fd(" ", node->pipe.out);
		args++;
	}
	if (new_line)
		ft_putstr_fd("\n", node->pipe.out);
	return (0);
}
