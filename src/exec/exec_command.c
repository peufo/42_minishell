/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:47:50 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/03 18:49:03 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	exec_redirect_open(node, node->redir.files_in, O_RDONLY, STDIN_FILENO);
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
}

int	exec_command(t_ast *node)
{
	lexer(node, node->line);
	exec_update_underscore(node);
	exec_redirect(node);
	if (node->status)
		return (node->status);
	if (!node->tokens)
		return (exec_redir_restore_std(node), node->status);
	node->builtin = get_builtin(*node->tokens);
	if (node->builtin)
		node->status = node->builtin(node);
	else if (node->is_child_process)
		node->status = exec_bin(node);
	else
	{
		signal(SIGINT, SIG_IGN);
		exec_child(node, exec_bin);
		node->status = waitstatus(node->pid);
		signal(SIGINT, &handle_signal);
	}
	exec_redir_restore_std(node);
	node->shell->exit_status = node->status;
	return (node->status);
}
