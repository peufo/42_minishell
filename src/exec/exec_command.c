/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:47:50 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/25 16:19:28 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_redirect_open(t_ast *node)
{
	char	**files;

	if (!node->files_out)
		return ;
	node->fd_std_out = dup(STDOUT_FILENO);
	files = node->files_out;
	while (*files)
	{
		node->fd_out = open(*files, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (node->fd_out == -1)
			shell_exit(node->shell);
		if (!(files + 1))
			close(node->fd_out);
		else
			dup2(node->fd_out, STDOUT_FILENO);
		files++;
	}
}

static void	exec_redirect_close(t_ast *node)
{

	if (!node->files_out)
		return ;
	close(node->fd_out);
	dup2(node->fd_std_out, STDOUT_FILENO);
	close(node->fd_std_out);
}

static void	pick_redirections(t_ast *node, char ***files, char *token)
{
	char	**cursor;

	cursor = string_array_find_match(node->tokens, token);
	while (cursor)
	{
		if (!*(cursor + 1))
			return (throw_error("parse error", __FILE__, __LINE__));
		string_array_push(files, ft_strdup(*(cursor + 1)));
		string_array_delete(node->tokens, *cursor);
		string_array_delete(node->tokens, *cursor);
		cursor = string_array_find_match(cursor, token);
	}
}

int	exec_command(t_ast *node)
{
	t_exe	builtin;

	pick_redirections(node, &node->files_in, "<");
	pick_redirections(node, &node->files_out, ">");
	exec_redirect_open(node);
	builtin = get_builtin(*node->tokens);
	if (builtin)
	{
		node->status = builtin(node);
		exec_redirect_close(node);
		return (node->status);
	}
	exec_child(node, exec_bin);
	exec_redirect_close(node);
	waitpid(node->pid, &node->status, 0);
	return (node->status);
}
