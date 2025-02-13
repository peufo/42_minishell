/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:08:17 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/12 11:13:57 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (0);
		else
			return (throw_error("What ", __FILE__, __LINE__), 0);
	}
	return (0);
}

int	executor(t_sh *shell)
{
	t_bfunc	builtin;

	if (!shell->ast->args)
		return (0);
	builtin = get_builtin(*shell->ast->args);
	if (builtin)
		return (builtin(shell));
	if (!exec_ast(shell, shell->ast))
		debug(shell, "ast executed\n");
	return (0);
}
