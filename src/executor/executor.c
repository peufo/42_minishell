/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:08:17 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/17 17:51:58 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	simple_exec(t_sh *shell)
{
	t_bfunc	builtin;

	builtin = get_builtin(*shell->ast->args);
	if (builtin)
		return (builtin(shell), 0);
	return (exec_bin(shell));
}

int	exec_ast(t_sh *shell, t_ast *node)
{
	if (node == NULL)
		return (0);
	if (node->type != AST_END)
	{
		if (node->type == AST_COMMAND)
			exec_handle_command(shell, node);
		else if (node->type == AST_PIPELINE)
			exec_handle_pipeline(shell, node);
		else if (node->type == AST_REDIRECT)
			exec_handle_redirection(shell, node);
		else if (node->type == AST_LOGICAL)
			exec_handle_logical(shell, node);
		else if (node->type == AST_SCRIPT)
			return (simple_exec(shell));
		else
			return (throw_error("What ", __FILE__, __LINE__), 0);
	}
	return (0);
}

int	executor(t_sh *shell)
{
	if (!shell->ast->args)
		return (0);
	if (!exec_ast(shell, shell->ast))
		debug(shell, "ast executed\n");
	return (0);
}
