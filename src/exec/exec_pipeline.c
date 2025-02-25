/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:53:27 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/23 18:07:06 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipeline(t_ast *node)
{
	t_pipe	*pipes;
	int		i;

	i = 0;
	while (node->children[i])
		i++;
	pipes = ft_calloc(i - 1, sizeof(*pipes));
	if (!pipes)
		return (shell_exit(node->shell), 1);
	while (--i)
	{
		pipe(pipes[i - 1].fildes);
		node->children[i]->pipe_in = pipes + i - 1;
		node->children[i - 1]->pipe_out = pipes + i - 1;
		exec_child(node->children[i], get_exe(node->children[i]));
	}
	exec_child(node->children[i], get_exe(node->children[i]));
	while (node->children[i])
	{
		waitpid(node->children[i]->pid, &node->children[i]->status, 0);
		i++;
	}
	free(pipes);
	return (node->children[i - 1]->status);
}
