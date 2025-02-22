/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:53:27 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/22 23:15:52 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exe	get_exe(t_ast *node)
{
	t_exe	builtin;

	builtin = get_builtin(*node->args);
	if (builtin)
		return (builtin);
	return (exec_bin);
}

void	exec_handle_pipeline(t_ast *node)
{
	t_exe	exe;
	t_pipe	p;

	pipe(p.fildes);
	node->left->pipe_out = &p;
	node->right->pipe_in = &p;
	exe = get_exe(node->left);
	exec_child(node->left, exe);
	exe = get_exe(node->right);
	exec_child(node->right, exe);
	waitpid(node->left->pid, &node->left->status, 0);
	waitpid(node->right->pid, &node->right->status, 0);
	node->status = node->left->status | node->right->status;
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
