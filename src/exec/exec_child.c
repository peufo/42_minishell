/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:08:33 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/03 19:37:01 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipes_connect(t_ast *node)
{
	debug(node->shell, "PIPE_CONNECT_IN:\n");
	if (node->pipe_in)
	{
		if (close(node->pipe_in->in) == -1)
		debug(node->shell, "CLOSE PIPE_IN->IN FAILED");
		if (dup2(node->pipe_in->out, STDIN_FILENO) == -1)
		debug(node->shell, "DUP2 PIPE_IN->OUT FAILED");
	}
	debug(node->shell, "PIPE_CONNECT_OUT:\n");
	if (node->pipe_out)
	{
		if (close(node->pipe_out->out) == -1)
			debug(node->shell, "CLOSE PIPE_OUT->OUT FAILED\n");
		if (dup2(node->pipe_out->in, STDOUT_FILENO))
			debug(node->shell, "DUP2 PIPE_OUT->IN FAILED\n");
	}
}

static void	pipes_close(t_ast *node)
{
	if (node->pipe_in)
		if (close(node->pipe_in->out) == -1)
			debug(node->shell, "CLOSE PIPE_IN->OUT FAILED\n");
	if (node->pipe_out)
		if (close(node->pipe_out->in) == -1)
			debug(node->shell, "CLOSE PIPE_OUT->IN FAILED\n");
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
