/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:47:50 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/17 10:17:02 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_redirect_open(
	t_ast *node,
	char **files,
	int open_flags,
	int std_fd)
{
	int	fd;

	if (!files)
		return ;
	while (*files)
	{
		fd = open(*files, open_flags, 0666);
		if (fd == -1)
			shell_exit(node->shell);
		if (dup2(fd, std_fd) == -1)
			shell_exit(node->shell);
		if (close(fd) == -1)
			shell_exit(node->shell);
		files++;
	}
}

static void	exec_redir_save_std(t_ast *node)
{
	if (node->redir.files_out)
		node->redir.fd_std_out = dup(STDOUT_FILENO);
}

static void	exec_redir_restore_std(t_ast *node)
{
	if (node->redir.files_out)
	{
		dup2(node->redir.fd_std_out, STDOUT_FILENO);
		close(node->redir.fd_std_out);
	}
}

static void	exec_redirect(t_ast *node)
{
	static int	f_create = O_CREAT | O_WRONLY | O_TRUNC;
	static int	f_append = O_CREAT | O_WRONLY | O_APPEND;
	char		**files_out_append;
	char		**files_out;

	files_out = node->redir.files_out;
	files_out_append = node->redir.files_out_append;
	exec_redir_save_std(node);
	if (node->redir.is_last_append)
	{
		exec_redirect_open(node, files_out, f_create, STDOUT_FILENO);
		exec_redirect_open(node, files_out_append, f_append, STDOUT_FILENO);
	}
	else
	{
		exec_redirect_open(node, files_out_append, f_append, STDOUT_FILENO);
		exec_redirect_open(node, files_out, f_create, STDOUT_FILENO);
	}
	exec_redirect_open(node, node->redir.files_in, O_RDONLY, STDIN_FILENO);
}

int	exec_command(t_ast *node)
{
	t_exe	builtin;

	lex(node, node->line);
	exec_redirect(node);
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
		exec_redir_restore_std(node);
		node->shell->exit_status = node->status;
		return (node->status);
	}
	exec_child(node, exec_bin);
	node->status = waitstatus(node->pid);
	exec_redir_restore_std(node);
	node->shell->exit_status = node->status;
	return (node->status);
}
