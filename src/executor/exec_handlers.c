/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:53:27 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/18 11:32:35 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_handle_pipeline(t_sh *shell, t_ast *node)
{
	pid_t	pid;
	t_pipe	pip;

	debug(shell, "into exec pipeline\n");
	node->right->pipe.out = node->pipe.out;
	node->left->pipe.in = node->pipe.in;
	if (pipe(pip.in_out) == -1)
		return (shell_exit(shell));
	pid = fork();
	if (pid == -1)
		return (shell_exit(shell));
	if (pid == 0)	//	enfant
	{
		node->right->pipe.in = pip.in;
		exec_ast(shell, node->right);
		close(pip.in);
		close(pip.out);
		return (shell_exit(shell));
	}
	node->left->pipe.out = pip.out;
	exec_ast(shell, node->left);
	close(pip.in);
	close(pip.out);
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
