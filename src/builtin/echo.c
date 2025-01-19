/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:10:39 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/19 23:03:09 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(t_sh *shell, t_command *cmd)
{
	t_list	*arg;
	bool	new_line;
	char	*arg_str;

	if (!cmd->args)
		return (1);
	arg = cmd->args->next;
	if (!arg)
		new_line = true;
	else
		new_line = ft_strcmp(arg->content, "-n");
	if (!new_line)
		arg = arg->next;
	while (arg)
	{
		arg_str = arg->content;
		(void)arg_str;
		ft_putstr_fd(arg->content, shell->pipe.out);
		if (arg->next && arg->next->content)
			ft_putstr_fd(" ", shell->pipe.out);
		arg = arg->next;
	}
	if (new_line)
		ft_putstr_fd("\n", shell->pipe.out);
	return (0);
}
