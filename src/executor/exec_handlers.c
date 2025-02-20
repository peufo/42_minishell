/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:53:27 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/20 06:21:34 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_handle_pipeline(t_ast *node)
{
	pid_t	pid;
	t_pipe	pip;

	debug(node->shell, "into exec pipeline\n");
	node->right->pipe.out = node->pipe.out;
	node->left->pipe.in = node->pipe.in;
	if (pipe(pip.in_out) == -1)
		return (shell_exit(node->shell));
	pid = fork();
	if (pid == -1)
		return (shell_exit(node->shell));
	if (pid == 0)
	{
		node->right->pipe.in = pip.out;
		exec_ast(node->right);
		close(pip.in);
		close(pip.out);
		return (shell_exit(node->shell));
	}
	node->left->pipe.out = pip.in;
	exec_ast(node->left);
	close(pip.in);
	close(pip.out);
}

void	exec_handle_redirection(t_ast *node)
{
	debug(node->shell, "into exec pipeline\n");
	(void)node;
}

void	exec_handle_logical(t_ast *node)
{
	debug(node->shell, "into exec pipeline\n");
	if (node->op == AST_OP_OR && exec_ast(node->left))
		exec_ast(node->right);
	else if (!exec_ast(node->left))
		exec_ast(node->left);
}