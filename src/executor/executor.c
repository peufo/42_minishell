/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:08:17 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/22 22:55:13 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_command(t_ast *node)
{
	t_exe	builtin;

	builtin = get_builtin(*node->args);
	if (builtin)
		return (builtin(node));
	exec_child(node, exec_bin);
	waitpid(node->pid, &node->status, 0);
	return (node->status);
}

int	exec_ast(t_ast *node)
{
	if (node == NULL)
		return (0);
	if (node->type != AST_END)
	{
		if (node->type == AST_COMMAND)
			exec_command(node);
		else if (node->type == AST_PIPELINE)
			exec_handle_pipeline(node);
		else if (node->type == AST_REDIRECT)
			exec_handle_redirection(node);
		else if (node->type == AST_LOGICAL)
			exec_handle_logical(node);
		else if (node->type == AST_SCRIPT)
			return (exec_command(node));
		else
			return (throw_error("What ", __FILE__, __LINE__), 0);
	}
	return (0);
}

int	executor(t_sh *shell)
{
	if (!exec_ast(shell->ast))
		debug(shell, "ast executed\n");
	return (0);
}
