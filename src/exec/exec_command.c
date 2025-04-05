/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:47:50 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/05 12:15:20 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_redirect(void *void_node, void *void_redir)
{
	t_ast	*node;
	t_redir	*redir;
	int		fd;

	node = (t_ast *)void_node;
	redir = (t_redir *)void_redir;
	if (redir->type == REDIR_HEREDOC)
		return (0);
	exec_redir_save_std(node, redir->fd_std);
	fd = open(redir->name, redir->open_flags, 0666);
	if (fd == -1)
	{
		exec_redir_restore_std(node);
		if (errno == ENOENT)
			return (throw(node, (char *[]){redir->name, ENOENT_MSG, NULL}));
		if (errno == EISDIR)
			return (throw(node, (char *[]){redir->name, EISDIR_MSG, NULL}));
		return (throw(node, NULL));
	}
	if (dup2(fd, redir->fd_std) == -1)
		return (throw(node, NULL));
	if (close(fd) == -1)
		return (throw(node, NULL));
	return (0);
}

static int	exec_redirect_heredoc_void(void *void_node, void *void_redir)
{
	return (exec_redirect_heredoc((t_ast *)void_node, (t_redir *)void_redir));
}

int	exec_command(t_ast *node)
{
	lexer(node, node->line);
	exec_update_underscore(node);
	ft_lstiter(node->redir, node, exec_redirect_heredoc_void);
	ft_lstiter(node->redir, node, exec_redirect);
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
