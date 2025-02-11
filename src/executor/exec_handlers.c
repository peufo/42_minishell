/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:53:27 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/11 12:55:42 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_handle_pipeline(t_sh *shell, t_ast *node)
{
		debug(shell, "into exec pipeline\n");
	//	LOGIC
	exec_ast(shell, node->left);
	//	LOGIC TO LEFT (PID ET FD HANDLING)
	exec_ast(shell, node->right);
	//	LOGIC TO RIGHT (PID ET FD HANDLING)
}

void	exec_handle_redirection(t_sh *shell, t_ast *node)
{
	debug(shell, "into exec pipeline\n");
	(void)node;
	//	LOGIC
	//	apparemment assez bordelique
}

void	exec_handle_logical(t_sh *shell, t_ast *node)
{
	debug(shell, "into exec pipeline\n");
	if (node->op == AST_OP_OR && exec_ast(shell, node->left))
		exec_ast(shell, node->right);
	else if (!exec_ast(shell, node->left))
		exec_ast(shell, node->right);
}

void	exec_handle_command(t_sh *shell, t_ast *node)
{
	debug(shell, "into exec command\n");
	(void)node;
	//	choper le pid et executer
}
