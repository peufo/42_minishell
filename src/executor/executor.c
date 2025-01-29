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

void	print_AST(t_sh *shell)
{
	(void)shell;
}

int	executor(t_sh *shell)
{
	t_bfunc	builtin;

	return (0);
	print_AST(shell);
	shell->exec.cmd = shell->ast.cmd;
	if (!shell->exec.cmd.elements)
		return (0);
	builtin = get_builtin(&shell->exec.cmd);
	if (builtin)
		return (builtin(shell));
	printf("TODO: exec command (%s)\n", shell->exec.cmd.element.data.text);
	return (0);
}
