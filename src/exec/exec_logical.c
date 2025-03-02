/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:14:54 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/02 15:32:18 by jvoisard         ###   ########.fr       */
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
	return (exec_ast(*node->children));
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
