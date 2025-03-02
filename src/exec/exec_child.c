/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:08:33 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/02 16:13:57 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipes_connect(t_ast *node)
{
	if (node->pipe_in)
	{
		close(node->pipe_in->in);
		dup2(node->pipe_in->out, STDIN_FILENO);
	}
	if (node->pipe_out)
	{
		close(node->pipe_out->out);
		dup2(node->pipe_out->in, STDOUT_FILENO);
	}
}

static void	pipes_close(t_ast *node)
{
	if (node->pipe_in)
		close(node->pipe_in->out);
	if (node->pipe_out)
		close(node->pipe_out->in);
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
