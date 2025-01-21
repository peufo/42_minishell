/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:33:56 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/21 14:48:09 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_sh *shell, t_command *cmd)
{
	char	*pwd;

	(void)cmd;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (shell_exit(shell), 1);
	ft_putstr_fd(pwd, shell->pipe.out);
	ft_putstr_fd("\n", shell->pipe.out);
	return (0);
}
