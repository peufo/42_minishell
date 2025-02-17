/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:53:27 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/16 13:27:59 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_handle_pipeline(t_sh *shell, t_ast *node)
{
	debug(shell, "into exec pipeline\n");
	exec_ast(shell, node->left);
	exec_ast(shell, node->right);
}

void	exec_handle_redirection(t_sh *shell, t_ast *node)
{
	debug(shell, "into exec pipeline\n");
	(void)node;
}

void	exec_handle_logical(t_sh *shell, t_ast *node)
{
	debug(shell, "into exec pipeline\n");
	if (node->op == AST_OP_OR && exec_ast(shell, node->left))
		exec_ast(shell, node->right);
	else if (!exec_ast(shell, node->left))
		exec_ast(shell, node->left);
}

void	exec_handle_command(t_sh *shell, t_ast *node)
{
	t_bfunc	builtin;

	debug(shell, "into exec command\n");
	builtin = get_builtin(*node->args);
	if (builtin)
		builtin(shell);
	execve(node->args[0], node->args, shell->env);
}
