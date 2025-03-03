/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:47:50 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/02 19:05:25 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_redirect_open(t_ast *node)
{
	char	**files;

	if (!node->files_out)
		return ;
	node->fd_std_out = dup(STDOUT_FILENO);
	files = node->files_out;
	while (*files)
	{
		node->fd_out = open(*files, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (node->fd_out == -1)
			shell_exit(node->shell);
		if (!(files))
		{
			close(node->fd_out);
		}
		else
			dup2(node->fd_out, STDOUT_FILENO);
		files++;
	}
}

static void	exec_redirect_close(t_ast *node)
{
	if (!node->files_out)
		return ;
	close(node->fd_out);
	dup2(node->fd_std_out, STDOUT_FILENO);
	close(node->fd_std_out);
}

int	exec_command(t_ast *node)
{
	t_exe	builtin;

	lex(node);
	exec_pick_redirections(node, &node->files_in, "<");
	exec_pick_redirections(node, &node->files_out, ">");
	exec_redirect_open(node);
	builtin = get_builtin(*node->tokens);
	if (builtin)
	{
		node->status = builtin(node);
		exec_redirect_close(node);
		return (node->status);
	}
	exec_child(node, exec_bin);
	exec_redirect_close(node);
	waitpid(node->pid, &node->status, 0);
	return (node->status);
}
