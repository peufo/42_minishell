/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:08:33 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/07 16:29:54 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_debug(t_ast *node, char *msg)
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
	pipe_debug(node, "CONNECT");
	if (node->pipe_in)
	{
		if (close(node->pipe_in->in) == -1)
			pipe_debug(node, "CLOSE PIPE_IN->IN FAILED");
		if (dup2(node->pipe_in->out, STDIN_FILENO) == -1)
			pipe_debug(node, "DUP2 PIPE_IN->OUT FAILED");
		if (close(node->pipe_in->out) == -1)
			pipe_debug(node, "CLOSE PIPE_IN->OUT FAILED");
	}
	if (node->pipe_out)
	{
		if (close(node->pipe_out->out) == -1)
			pipe_debug(node, "CLOSE PIPE_OUT->OUT FAILED");
		if (dup2(node->pipe_out->in, STDOUT_FILENO) == -1)
			pipe_debug(node, "DUP2 PIPE_OUT->IN FAILED");
		if (close(node->pipe_out->in) == -1)
			pipe_debug(node, "CLOSE PIPE_OUT->IN FAILED");
	}
}

static void	pipes_close(t_ast *node)
{
	pipe_debug(node, "CLOSE");
	if (node->pipe_in)
		if (close(node->pipe_in->out) == -1)
			pipe_debug(node, "CLOSE PIPE_IN->OUT FAILED");
	if (node->pipe_out)
		if (close(node->pipe_out->in) == -1)
			pipe_debug(node, "CLOSE PIPE_OUT->IN FAILED");
}

void	exec_child(t_ast *node, t_exe exe)
{
	pipe_debug(node, "FORK");
	node->pid = fork();
	if (node->pid)
		return ;
	pipe_debug(node, "CHILD");
	ast_debug(node, 0);
	node->is_child_process = true;
	pipes_connect(node);
	node->status = exe(node);
	pipes_close(node);
	shell_exit(node->shell);
}
