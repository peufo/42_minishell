/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:08:17 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/19 19:37:47 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_sh *shell, t_command *cmd)
{
	t_bfunc	builtin;

	builtin = get_builtin(cmd);
	if (builtin)
		return (builtin(shell, cmd));
	printf("TODO: exec command (%s)\n", cmd->executable);
	return (0);
}