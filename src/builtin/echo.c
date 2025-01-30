/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:10:39 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/30 17:43:10 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(t_sh *shell)
{
	t_list	*arg;
	t_list	*args;
	bool	new_line;

	args = shell->ast.args;
	if (!args)
		return (1);
	arg = args->next;
	if (!arg)
		new_line = true;
	else
		new_line = ft_strcmp(((t_token *)arg->content)->value, "-n");
	if (!new_line)
		arg = arg->next;
	while (arg)
	{
		ft_putstr_fd(((t_token *)arg->content)->value, shell->pipe.out);
		if (arg->next && arg->next->content)
			ft_putstr_fd(" ", shell->pipe.out);
		arg = arg->next;
	}
	if (new_line)
		ft_putstr_fd("\n", shell->pipe.out);
	return (0);
}
