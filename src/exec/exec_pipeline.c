/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:53:27 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/04 15:41:21 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_children_count(t_ast *node)
{
	int	children_count;

	children_count = 0;
	while (node->children[children_count])
		children_count++;
	return (children_count);
}

static t_pipe	*pipes_create(t_ast *node)
{
	t_pipe	*pipes;
	int		children_count;

	children_count = get_children_count(node);
	pipes = ft_calloc(children_count - 1, sizeof(*pipes));
	if (!pipes)
		return (shell_exit(node->shell), NULL);
	return (pipes);
}

int	exec_pipeline(t_ast *node)
{
	int		i;
	t_pipe	*p;
	int		children_count;

	node->pipes = pipes_create(node);
	if (!node->pipes)
		return (shell_exit(node->shell), false);
	children_count = get_children_count(node);
	i = children_count;
	signal(SIGINT, SIG_IGN);
	while (--i)
	{
		p = &node->pipes[i - 1];
		pipe(p->fildes);
		node->children[i]->pipe_in = p;
		node->children[i - 1]->pipe_out = p;
		exec_child(node->children[i], exec_ast);
	}
	exec_child(node->children[i], exec_ast);
	while (node->children[i])
	{
		node->children[i]->status = waitstatus(node, node->children[i]->pid);
		i++;
	}
	signal(SIGINT, &handle_signal_int);
	node->shell->exit_status = node->children[i - 1]->status;
	return (node->shell->exit_status);
}
