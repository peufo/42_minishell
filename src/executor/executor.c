/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:08:17 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/30 17:40:59 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	debug_ast(t_sh *shell)
{
	debug(shell, "\ncmd:");
	debug(shell, shell->ast.toks[0]);
	debug(shell, "\n");
}

int	executor(t_sh *shell)
{
	t_bfunc	builtin;

	return (0);
	debug_ast(shell);
	builtin = get_builtin((shell->ast.toks[0]));
	if (builtin)
		return (builtin(shell));
	debug(shell, "TODO: exec command\n");
	return (0);
}
