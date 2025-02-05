/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:08:17 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/05 14:57:45 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_sh *shell)
{
	t_bfunc	builtin;

	if (!shell->ast.args)
		return (0);
	debug_ast(shell);
	builtin = get_builtin(*shell->ast.args);
	if (builtin)
		return (builtin(shell));
	debug(shell, "TODO: exec command\n");
	return (0);
}
