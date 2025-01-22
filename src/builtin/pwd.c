/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:33:56 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/22 15:17:17 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_sh *shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (shell_exit(shell), 1);
	ft_putstr_fd(pwd, shell->pipe.out);
	ft_putstr_fd("\n", shell->pipe.out);
	free(pwd);
	return (0);
}
