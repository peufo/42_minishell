/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:06:26 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/24 09:01:28 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_great(t_ast *node)
{
	int		fd;
	t_pipe	p;

	fd = open(*node->children[1]->tokens, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (1);
	pipe(p.fildes);
	dup2(fd, p.in);
	close(p.out);
	node->children[0]->pipe_out = &p;
	exec_child(node->children[0], get_exe(node->children[0]));
	return (node->children[0]->status);
}

int	exec_dgreat(t_ast *node)
{
	int		fd;
	t_pipe	p;

	fd = open(*node->children[1]->tokens, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
		return (1);
	pipe(p.fildes);
	close(p.out);
	dup2(fd, p.in);
	node->children[0]->pipe_out = &p;
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
	debug(node->shell, "TODO: exec dless");
	return (0);
}
