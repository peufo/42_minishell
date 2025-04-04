/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_std.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 11:44:42 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/04 23:59:18 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_redir_save_std(t_ast *node, int fd_std)
{
	if (node->is_child_process)
		return ;
	if (!node->fd_std_out && fd_std == STDOUT_FILENO)
	{
		node->fd_std_out = dup(STDOUT_FILENO);
		if (node->fd_std_out == -1)
			shell_exit(node->shell);
	}
	if (!node->fd_std_in && fd_std == STDIN_FILENO)
	{
		node->fd_std_in = dup(STDIN_FILENO);
		if (node->fd_std_in == -1)
			shell_exit(node->shell);
	}
}

void	exec_redir_restore_std(t_ast *node)
{
	if (node->fd_std_out)
	{
		dup2(node->fd_std_out, STDOUT_FILENO);
		close(node->fd_std_out);
		node->fd_std_out = 0;
	}
	if (node->fd_std_in)
	{
		dup2(node->fd_std_in, STDIN_FILENO);
		close(node->fd_std_in);
		node->fd_std_in = 0;
	}
}
