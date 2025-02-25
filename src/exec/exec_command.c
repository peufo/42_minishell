/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:47:50 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/25 00:38:05 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_redirect_open(t_ast *node)
{
	char	**files;
	int		*fildes;

	if (!node->files_out)
		return ;
	files = node->files_out;
	fildes = node->fildes_out;
	while (*files)
	{
		*fildes = open(*(files++), O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (*fildes == -1)
			shell_exit(node->shell);
		dup2(*fildes, STDOUT_FILENO);
		fildes++;
	}
}

static void	exec_redirect_close(t_ast *node)
{
	char	**files;
	int		*fildes;

	if (!node->files_out)
		return ;
	files = node->files_out;
	fildes = node->fildes_out;
	while (*files)
	{
		close(*(fildes++));
		files++;
	}
}

int	exec_command(t_ast *node)
{
	t_exe	builtin;

	exec_redirect_open(node);
	builtin = get_builtin(*node->tokens);
	if (builtin)
	{
		node->status = builtin(node);
		exec_redirect_close(node);
		return (node->status);
	}
	exec_child(node, exec_bin);
	waitpid(node->pid, &node->status, 0);
	exec_redirect_close(node);
	return (node->status);
}
