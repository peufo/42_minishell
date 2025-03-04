/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:08:33 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/04 14:07:13 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipes_connect(t_ast *node)
{
	DEBUG("CHILD_CONNECT [%s]\n", node->line);
	if (node->pipe_in)
	{
		if (close(node->pipe_in->in) == -1)
			DEBUG("CLOSE PIPE_IN->IN FAILED\n");
		if (dup2(node->pipe_in->out, STDIN_FILENO) == -1)
			DEBUG("DUP2 PIPE_IN->OUT FAILED\n");
	}
	if (node->pipe_out)
	{
		if (close(node->pipe_out->out) == -1)
			DEBUG("CLOSE PIPE_OUT->OUT FAILED\n");
		if (dup2(node->pipe_out->in, STDOUT_FILENO))
			DEBUG("DUP2 PIPE_OUT->IN FAILED\n");
	}
}

static void	pipes_close(t_ast *node)
{
	if (node->pipe_in)
		if (close(node->pipe_in->out) == -1)
			DEBUG("CLOSE PIPE_IN->OUT FAILED\n");
	if (node->pipe_out)
		if (close(node->pipe_out->in) == -1)
			DEBUG("CLOSE PIPE_OUT->IN FAILED\n");
}

void	exec_child(t_ast *node, t_exe exe)
{
	node->pid = fork();
	if (node->pid)
	{
		pipes_close(node);
		return ;
	}
	pipes_connect(node);
	node->status = exe(node);
	pipes_close(node);
	shell_exit(node->shell);
}
