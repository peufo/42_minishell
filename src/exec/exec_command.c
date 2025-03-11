/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:47:50 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/11 23:19:41 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_redirect_open(t_ast *node, int open_flags)
{
	char	**files;

	if (!node->redir.files_out)
		return ;
	node->redir.fd_std_out = dup(STDOUT_FILENO);
	files = node->redir.files_out;
	while (*files)
	{
		node->redir.fd_out = open(*files, open_flags, 0666);
		if (node->redir.fd_out == -1)
			shell_exit(node->shell);
		if (!*(files + 1))
			if (dup2(node->redir.fd_out, STDOUT_FILENO) == -1)
				shell_exit(node->shell);		
		if (close(node->redir.fd_out) == -1)
			shell_exit(node->shell);
		files++;
	}
}

static void	exec_redir_restore_std(t_ast *node)
{
	if (!node->redir.files_out)
		return ;
	dup2(node->redir.fd_std_out, STDOUT_FILENO);
	close(node->redir.fd_std_out);
}

// TODO: handle redirect INPUT & APPEND
int	exec_command(t_ast *node)
{
	t_exe	builtin;

	lex(node, node->line);
	exec_redirect_open(node, O_WRONLY | O_CREAT | O_TRUNC);
	builtin = get_builtin(*node->tokens);
	if (builtin)
	{
		node->status = builtin(node);
		node->shell->exit_status = node->status;
		exec_redir_restore_std(node);
		return (node->status);
	}
	if (node->is_child_process)
	{
		node->status = exec_bin(node);
		node->shell->exit_status = node->status;
		return (node->status);
	}
	exec_child(node, exec_bin);
	exec_redir_restore_std(node);
	node->status = waitstatus(node->pid);
	node->shell->exit_status = node->status;
	return (node->status);
}
