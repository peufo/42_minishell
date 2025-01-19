/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 23:15:32 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/19 23:32:36 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_sh *shell, t_command *cmd)
{
	char	**env;

	(void)cmd;
	env = shell->env;
	while (*env)
	{
		ft_putstr_fd(*env, shell->pipe.out);
		ft_putstr_fd("\n", shell->pipe.out);
		env++;
	}
	return (0);
}
