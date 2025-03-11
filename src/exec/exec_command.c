/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:47:50 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/11 23:46:55 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_redirect_open(
	t_ast *node,
	char **files,
	int open_flags,
	int std_fd
)
{
	int	fd;

	if (!files)
		return ;
	while (*files)
	{
		fd = open(*files, open_flags, 0666);
		if (fd == -1)
			shell_exit(node->shell);
		if (!*(files + 1))
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
	exec_redir_save_std(node);
	exec_redirect_open(node,
		node->redir.files_out,
		O_WRONLY | O_CREAT | O_TRUNC,
		STDOUT_FILENO);
	exec_redirect_open(node, node->redir.files_in, O_RDONLY, STDIN_FILENO);
}

// TODO: handle redirect INPUT & APPEND
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
