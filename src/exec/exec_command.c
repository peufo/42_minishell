/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:47:50 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/17 19:00:38 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_redirect_open(
	t_ast *node,
	char **files,
	int open_flags,
	int std_fd)
{
	int	fd;

	if (!files)
		return (0);
	while (*files)
	{
		fd = open(*files, open_flags, 0666);
		if (fd == -1)
			return (throw(node, NULL));
		if (dup2(fd, std_fd) == -1)
			return (throw(node, NULL));
		if (close(fd) == -1)
			return (throw(node, NULL));
		files++;
	}
	return (0);
}

static void	exec_redir_save_std(t_ast *node)
{
	if (node->redir.files_out || node->redir.files_out_append)
		node->redir.fd_std_out = dup(STDOUT_FILENO);
}

static void	exec_redir_restore_std(t_ast *node)
{
	if (node->redir.files_out || node->redir.files_out_append)
	{
		dup2(node->redir.fd_std_out, STDOUT_FILENO);
		close(node->redir.fd_std_out);
	}
}

static void	exec_redirect(t_ast *node, char **files_in)
{
	static int	f_create = O_CREAT | O_WRONLY | O_TRUNC;
	static int	f_append = O_CREAT | O_WRONLY | O_APPEND;
	char		**files_append;
	char		**files_out;

	if (!files_in || !*files_in)
		return ;
	files_out = node->redir.files_out;
	files_append = node->redir.files_out_append;
	exec_redir_save_std(node);
	if (node->redir.is_last_append)
	{
		exec_redirect_open(node, files_out, f_create, STDOUT_FILENO);
		exec_redirect_open(node, files_append, f_append, STDOUT_FILENO);
	}
	else
	{
		exec_redirect_open(node, files_append, f_append, STDOUT_FILENO);
		exec_redirect_open(node, files_out, f_create, STDOUT_FILENO);
	}
	exec_redirect_open(node, files_in, O_RDONLY, STDIN_FILENO);
}

int	exec_command(t_ast *node)
{
	t_exe	builtin;

	lex(node, node->line);
	exec_redirect_open(node, node->heredoc.files_in, O_RDONLY, STDIN_FILENO);
	exec_redirect(node);
	if (!node->tokens)
	{
		exec_redir_restore_std(node);
		return (node->status);
	}
	builtin = get_builtin(*node->tokens);
	if (builtin)
		node->status = builtin(node);
	else if (node->is_child_process)
		node->status = exec_bin(node);
	else
	{
		exec_child(node, exec_bin);
		node->status = waitstatus(node->pid);
	}
	exec_redir_restore_std(node);
	node->shell->exit_status = node->status;
	return (node->status);
}
