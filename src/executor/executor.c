/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:08:17 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/22 15:26:01 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_sh *shell)
{
	t_bfunc	builtin;

	shell->exec.cmd = shell->parser.cmd;
	if (!shell->exec.cmd.args)
		return (0);
	builtin = get_builtin(&shell->exec.cmd);
	if (builtin)
		return (builtin(shell));
	printf("TODO: exec command (%s)\n", (char *)shell->exec.cmd.args->content);
	return (0);
}
