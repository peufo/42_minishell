/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:14:54 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/04 15:54:38 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clone_pipes(t_ast *parent, t_ast *child)
{
	child->pipe_in = parent->pipe_in;
	child->pipe_out = parent->pipe_out;
}

int	exec_subshell(t_ast *node)
{
	clone_pipes(node, *node->children);
	signal(SIGINT, SIG_IGN);
	exec_child(*node->children, exec_ast);
	(*node->children)->status = waitstatus(node, (*node->children)->pid);
	signal(SIGINT, handle_signal_int);
	return ((*node->children)->status);
}

int	exec_and(t_ast *node)
{
	clone_pipes(node, node->children[0]);
	clone_pipes(node, node->children[1]);
	if (exec_ast(node->children[0]))
		return (node->children[0]->status);
	return (exec_ast(node->children[1]));
}

int	exec_or(t_ast *node)
{
	clone_pipes(node, node->children[0]);
	clone_pipes(node, node->children[1]);
	if (!exec_ast(node->children[0]))
		return (0);
	return (exec_ast(node->children[1]));
}
