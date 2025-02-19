/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:08:17 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/19 13:05:03 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(t_sh *shell, t_ast *node)
{
	t_bfunc	builtin;

	if (node->pipe.in != STDIN_FILENO)
		dup2(STDIN_FILENO, node->pipe.in);
	if (node->pipe.out != STDOUT_FILENO)
		dup2(STDOUT_FILENO, node->pipe.out);
	builtin = get_builtin(*node->args);
	if (builtin)
		return (builtin(shell), 0);
	return (exec_bin(shell, node));
}

int	exec_ast(t_sh *shell, t_ast *node)
{
	if (node == NULL)
		return (0);
	if (node->type != AST_END)
	{
		if (node->type == AST_COMMAND)
			exec(shell, node);
		else if (node->type == AST_PIPELINE)
			exec_handle_pipeline(shell, node);
		else if (node->type == AST_REDIRECT)
			exec_handle_redirection(shell, node);
		else if (node->type == AST_LOGICAL)
			exec_handle_logical(shell, node);
		else if (node->type == AST_SCRIPT)
			return (exec(shell, node));
		else
			return (throw_error("What ", __FILE__, __LINE__), 0);
	}
	return (0);
}

int	executor(t_sh *shell)
{
	shell->ast->pipe = shell->pipe;
	if (!exec_ast(shell, shell->ast))
		debug(shell, "ast executed\n");
	return (0);
}
