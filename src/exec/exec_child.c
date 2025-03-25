/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:08:33 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/25 17:51:03 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fd(t_ast *node, int fd)
{
	if (close(fd) == -1)
		shell_exit(node->shell);
}

static void	pipes_connect(t_ast *node)
{
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
	node->is_child_process = true;
	pipes_connect(node);
	node->status = exe(node);
	shell_exit(node->shell);
}
