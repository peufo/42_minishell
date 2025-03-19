/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:08:33 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/19 10:03:16 by dyodlm           ###   ########.fr       */
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

static void	close_fd(t_ast *node, int fd)
{
	if (close(fd) == -1)
		shell_exit(node->shell);
}

static void	pipes_inv_connect(t_ast *node)
{
	printf("poop\n");
	return ;
	if (node->pipe_in)
	{
		close_fd(node, node->pipe_in->in);
		if (dup2(node->pipe_in->out, STDIN_FILENO) == -1)
			shell_exit(node->shell);
		close_fd(node, node->pipe_in->out);
	}
	if (node->pipe_out)
	{
		close_fd(node, node->pipe_out->out);
		if (dup2(node->pipe_out->in, STDOUT_FILENO) == -1)
			shell_exit(node->shell);
		close_fd(node, node->pipe_out->in);
	}
}
static void	pipes_connect(t_ast *node)
{
	pipe_debug(node, "CONNECT");
	if (node->heredoc.files_in || node->heredoc.fd_in == 4)
		return (pipes_inv_connect(node));
	if (node->pipe_in)
	{
		close_fd(node, node->pipe_in->in);
		if (dup2(node->pipe_in->out, STDIN_FILENO) == -1)
			shell_exit(node->shell);
		close_fd(node, node->pipe_in->out);
	}
	if (node->pipe_out)
	{
		close_fd(node, node->pipe_out->out);
		if (dup2(node->pipe_out->in, STDOUT_FILENO) == -1)
			shell_exit(node->shell);
		close_fd(node, node->pipe_out->in);
	}
}

void	exec_child(t_ast *node, t_exe exe)
{
	pipe_debug(node, "FORK");
	node->pid = fork();
	if (node->pid)
	{
		if (node->pipe_out)
		{
			close_fd(node, node->pipe_out->out);
			close_fd(node, node->pipe_out->in);
		}
		return ;
	}
	pipe_debug(node, "CHILD");
	ast_debug(node, 0);
	node->is_child_process = true;
	pipes_connect(node);
	node->status = exe(node);
	shell_exit(node->shell);
}
