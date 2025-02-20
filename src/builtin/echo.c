/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:10:39 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/20 06:16:56 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(t_ast *node)
{
	char	**args;
	bool	new_line;

	args = node->args + 1;
	if (!*args)
		new_line = true;
	else
		new_line = ft_strcmp(*args, "-n");
	if (!new_line)
		args++;
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
