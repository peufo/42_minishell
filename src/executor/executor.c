/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:08:17 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/30 12:37:59 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_ast(t_sh *shell)
{
	(void)shell;
}

int	executor(t_sh *shell)
{
	t_bfunc	builtin;

	return (0);
	print_ast(shell);
	if (!shell->ast.cmd.args)
		return (printf("no elements to exec\n"), 0);
	builtin = get_builtin(&shell->ast.cmd);
	if (builtin)
		return (builtin(shell));
	printf("TODO: exec command (%s)\n", shell->ast.cmd.arg.data.text);
	return (0);
}
