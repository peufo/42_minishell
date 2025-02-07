/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:08:17 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/07 09:56:24 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_sh *shell)
{
	t_bfunc	builtin;

	if (!shell->ast->args)
		return (0);
	debug_ast(shell);
	builtin = get_builtin(*shell->ast->args);
	if (builtin)
		return (builtin(shell));
	debug(shell, "TODO: exec command\n");
	return (0);
}
