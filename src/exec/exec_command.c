/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:47:50 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/28 11:20:40 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_redir_save_std(t_ast *node)
{
	t_redir	*rh;

	rh = &node->redir;
	if (rh->files_out || rh->files_out_append)
	{
		rh->fd_std_out = dup(STDOUT_FILENO);
		if (rh->fd_std_out == -1)
			shell_exit(node->shell);
	}
	if (rh->files_in)
	{
		rh->fd_std_in = dup(STDIN_FILENO);
		if (rh->fd_std_in == -1)
			shell_exit(node->shell);
	}
}

static void	exec_redir_restore_std(t_ast *node)
{
	t_redir *rh;

	rh = &node->redir;
	if (rh->files_out || rh->files_out_append)
	{
		dup2(rh->fd_std_out, STDOUT_FILENO);
		close(rh->fd_std_out);
	}
	if (rh->files_in)
	{
		dup2(rh->fd_std_in, STDIN_FILENO);
		close(rh->fd_std_in);
	}
}

static int	exec_redirect_open(
	t_ast *node,
	char **files,
	int open_flags,
	int std_fd)
{
	int			fd;
	static char	no_file_err[] = ": No such file or directory";
	static char	is_dir_err[] = ": Is a directory";

	if (!files)
		return (0);
	while (*files)
	{
		fd = open(*files, open_flags, 0666);
		if (fd == -1)
		{
			exec_redir_restore_std(node);
			if (errno == ENOENT)
				return (throw(node, (char *[]){*files, no_file_err, NULL}), 1);
			if (errno == EISDIR)
				return (throw(node, (char *[]){*files, is_dir_err, NULL}), 1);
			return (throw(node, NULL));
		}
		if (dup2(fd, std_fd) == -1)
			return (throw(node, NULL));
		if (close(fd) == -1)
			return (throw(node, NULL));
		files++;
	}
	return (0);
}

static void	exec_redirect(t_ast *node)
{
	static int	f_create = O_CREAT | O_WRONLY | O_TRUNC;
	static int	f_append = O_CREAT | O_WRONLY | O_APPEND;
	char		**files_append;
	char		**files_out;

	files_out = node->redir.files_out;
	files_append = node->redir.files_out_append;
	exec_redir_save_std(node);
	if (node->heredoc.files_in)
		exec_redirect_open(node,
			node->heredoc.files_in,
			O_RDONLY, STDIN_FILENO);
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
	exec_redirect_open(node, node->redir.files_in, O_RDONLY, STDIN_FILENO);
}

int	exec_command(t_ast *node)
{
	t_exe	builtin;

	lex(node, node->line);
	exec_update_underscore(node);
	exec_redirect_open(node, node->heredoc.files_in, O_RDONLY, STDERR_FILENO);
	exec_redirect(node);
	if (node->status)
		return (node->status);
	if (!node->tokens)
		return (exec_redir_restore_std(node), node->status);
	builtin = get_builtin(*node->tokens);
	if (builtin)
	{
		node->status = builtin(node);
		exec_redir_restore_std(node);
	}
	else if (node->is_child_process)
	{
		node->status = exec_bin(node);
		exec_redir_restore_std(node);
	}
	else
	{
		exec_redir_restore_std(node);
		signal(SIGINT, SIG_IGN);
		exec_child(node, exec_bin);
		node->status = waitstatus(node->pid);
		signal(SIGINT, &handle_signal);
	}
	node->shell->exit_status = node->status;
	return (node->status);
}
