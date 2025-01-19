/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:10:39 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/19 19:37:11 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(t_sh *shell, t_command *cmd)
{
	t_list	*arg;

	if (!cmd->args)
		return (1);
	arg = cmd->args->next;
	while (arg)
	{
		ft_putstr_fd(arg->content, shell->pipe.out);
		ft_putstr_fd(" ", shell->pipe.out);
		arg = arg->next;
	}
	ft_putstr_fd("\n", shell->pipe.out);
	return (0);
}
