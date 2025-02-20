/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:08:17 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/20 08:53:46 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_command(t_ast *node)
{
	t_bfunc	builtin;

	builtin = get_builtin(*node->args);
	if (builtin)
		return (builtin(node), 0);
	return (exec_bin(node));
}

int	exec_ast(t_ast *node)
{
	if (node == NULL)
		return (0);
	if (node->type != AST_END)
	{
		if (node->type == AST_COMMAND)
			exec_command(node);
		else if (node->type == AST_PIPELINE)
			exec_handle_pipeline(node);
		else if (node->type == AST_REDIRECT)
			exec_handle_redirection(node);
		else if (node->type == AST_LOGICAL)
			exec_handle_logical(node);
		else if (node->type == AST_SCRIPT)
			return (exec_command(node));
		else
			return (throw_error("What ", __FILE__, __LINE__), 0);
	}
	return (0);
}

int	executor(t_sh *shell)
{
	shell->ast->pipe = shell->pipe;
	if (!exec_ast(shell->ast))
		debug(shell, "ast executed\n");
	return (0);
}
