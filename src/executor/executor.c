/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:08:17 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/21 18:48:41 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_sh *shell, t_cmd *cmd)
{
	t_bfunc	builtin;

	if (!cmd->executable)
		return (0);
	builtin = get_builtin(cmd);
	if (builtin)
		return (builtin(shell, cmd));
	printf("TODO: exec command (%s)\n", cmd->executable);
	return (0);
}
