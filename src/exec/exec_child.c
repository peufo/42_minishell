/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:08:33 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/05 12:51:12 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	debug_pipe(t_ast *node, char *msg)
{
	if (node->pipe_in && node->pipe_out)
		DEBUG("[%d]\t%d→%d()%d→%d\t%s\n",
			getpid(),
			node->pipe_in->in,
			node->pipe_in->out,
			node->pipe_out->in,
			node->pipe_out->out,
			msg);
	if (!node->pipe_in && node->pipe_out)
		DEBUG("[%d]\t-→-()%d→%d\t%s\n",
			getpid(),
			node->pipe_out->in,
			node->pipe_out->out,
			msg);
	if (node->pipe_in && !node->pipe_out)
		DEBUG("[%d]\t%d→%d()-→-\t%s\n",
			getpid(),
			node->pipe_in->in,
			node->pipe_in->out,
			msg);
	if (!node->pipe_in && !node->pipe_out)
		DEBUG("[%d]\t-→-()-→-\t%s\n", getpid(), msg);
}

static void	pipes_connect(t_ast *node)
{
	debug_pipe(node, "CONNECT");
	if (node->pipe_in)
	{
		if (close(node->pipe_in->in) == -1)
			debug_pipe(node, "CLOSE PIPE_IN->IN FAILED");
		if (dup2(node->pipe_in->out, STDIN_FILENO) == -1)
			debug_pipe(node, "DUP2 PIPE_IN->OUT FAILED");
	}
	if (node->pipe_out)
	{
		if (close(node->pipe_out->out) == -1)
			debug_pipe(node, "CLOSE PIPE_OUT->OUT FAILED");
		if (dup2(node->pipe_out->in, STDOUT_FILENO))
			debug_pipe(node, "DUP2 PIPE_OUT->IN FAILED");
	}
}

static void	pipes_close(t_ast *node)
{
	debug_pipe(node, "CLOSE");
	if (node->pipe_in)
		if (close(node->pipe_in->out) == -1)
			debug_pipe(node, "CLOSE PIPE_IN->OUT FAILED");
	if (node->pipe_out)
		if (close(node->pipe_out->in) == -1)
			debug_pipe(node, "CLOSE PIPE_OUT->IN FAILED");
}

void	exec_child(t_ast *node, t_exe exe)
{
	debug_pipe(node, "FORK");
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
