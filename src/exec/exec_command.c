/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:47:50 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/10 14:58:50 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// >
static void	exec_redirect_open(t_ast *node)
{
	char	**files;

	if (!node->redir.files_out)
		return ;
	node->redir.fd_std_out = dup(STDOUT_FILENO);
	files = node->redir.files_out;
	while (*files)
	{
		// >>   O_TRUNC O_APPEND
		node->redir.fd_out = open(*files, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (node->redir.fd_out == -1)
			shell_exit(node->shell);
		if (!(files))
		{
			close(node->redir.fd_out);
		}
		else
		dup2(node->redir.fd_out, STDOUT_FILENO);
		files++;
	}
}

static void	exec_redirect_close(t_ast *node)
{
	if (!node->redir.files_out)
		return ;
	close(node->redir.fd_out);
	dup2(node->redir.fd_std_out, STDOUT_FILENO);
	close(node->redir.fd_std_out);
}

// TODO: handle redirect INPUT & APPEND
int	exec_command(t_ast *node)
{
	t_exe	builtin;

	lex(node, node->line);
	exec_redirect_open(node);
	builtin = get_builtin(*node->tokens);
//	printf("Exec command\n");
	if (builtin)
	{
//		printf("Builtin\n");
		node->status = builtin(node);
		node->shell->exit_status = node->status;
		exec_redirect_close(node);
		return (node->status);
	}
	if (node->is_child_process)
	{
//		printf("Children\n");
		node->status = exec_bin(node);
		node->shell->exit_status = node->status;
		return (node->status);
	}
	exec_child(node, exec_bin);
	exec_redirect_close(node);
	node->status = waitstatus(node->pid);
	node->shell->exit_status = node->status;
	return (node->status);
}
