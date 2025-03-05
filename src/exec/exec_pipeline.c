/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:53:27 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/05 13:22:36 by jvoisard         ###   ########.fr       */
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

static void	pipes_close(t_ast *node)
{
	int	children_count;
	int	i;

	children_count = get_children_count(node);
	i = 0;
	while (i < children_count - 1)
	{
		close(node->pipes[i].in);
		close(node->pipes[i].out);
		i++;
	}
	return ;
}

int	exec_pipeline(t_ast *node)
{
	int		i;
	t_pipe	*p;

	node->pipes = pipes_create(node);
	if (!node->pipes)
		return (shell_exit(node->shell), false);
	i = get_children_count(node);
	while (--i)
	{
		p = &node->pipes[i - 1];
		pipe(p->fildes);
		node->children[i]->pipe_in = p;
		node->children[i - 1]->pipe_out = p;
		exec_child(node->children[i], exec_ast);
	}
	exec_child(node->children[i], exec_ast);
	pipes_close(node);
	while (node->children[i])
	{
		waitpid(node->children[i]->pid, &node->children[i]->status, 0);
		i++;
	}
	return (node->children[i - 1]->status);
}
