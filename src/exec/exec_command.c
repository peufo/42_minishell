/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:47:50 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/05 22:38:19 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_redir(t_ast *node, t_redir *redir)
{
	exec_redir_save_std(node, redir->fd_std);
	if (!redir->fd)
		redir->fd = open(redir->name, redir->open_flags);
	if (redir->fd == -1)
	{
		exec_redir_restore_std(node);
		if (errno == ENOENT)
			return (throw(node, (char *[]){redir->name, ENOENT_MSG, NULL}));
		if (errno == EISDIR)
			return (throw(node, (char *[]){redir->name, EISDIR_MSG, NULL}));
		return (throw(node, NULL));
	}
	if (dup2(redir->fd, redir->fd_std) == -1)
		return (throw(node, NULL));
	if (close(redir->fd) == -1)
		return (throw(node, NULL));
	return (0);
}

int	exec_command(t_ast *node)
{
	node->tokens = lexer(node, node->line);
	exec_update_underscore(node);
	ft_lstiter(node->redir, node, (int (*)(void *, void *))exec_redir_heredoc);
	if (node->status)
		return (node->status);
	ft_lstiter(node->redir, node, (int (*)(void *, void *))exec_redir);
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
		node->status = waitstatus(node, node->pid);
		signal(SIGINT, handle_signal_int);
	}
	exec_redir_restore_std(node);
	node->shell->exit_status = node->status;
	return (node->status);
}
