/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:06:26 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/24 21:40:42 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_great(t_ast *node)
{
	int		fd;
	t_exe	exe;

	node->pid = fork();
	if (node->pid)
	{
		waitpid(node->pid, &node->status, 0);
		return (node->status);
	}
	fd = open(*node->children[1]->tokens, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (1);
	dup2(fd, STDOUT_FILENO);
	exe = get_exe(node->children[0]);
	node->children[0]->status = exe(node->children[0]);
	close(fd);
	exit(node->children[0]->status);
	return (node->children[0]->status);
}

int	exec_dgreat(t_ast *node)
{
	int		fd;
	t_pipe	redir_pipe;

	fd = open(*node->children[1]->tokens, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
		return (1);
	pipe(redir_pipe.fildes);
	close(redir_pipe.out);
	dup2(fd, redir_pipe.in);
	node->children[0]->pipe_out = &redir_pipe;
	exec_child(node->children[0], get_exe(node->children[0]));
	return (node->children[0]->status);
}

int	exec_less(t_ast *node)
{
	debug(node->shell, "TODO: exec less");
	return (0);
}

int	exec_dless(t_ast *node)
{
	debug(node->shell, "TODO: RM this because this is handled on lexer");
	return (0);
}
