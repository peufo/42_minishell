/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:08:17 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/13 00:27:05 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_ast(t_ast *node)
{
	t_exe			handler;
	static t_exe	handlers[] = {
	[AST_COMMAND] = exec_command,
	[AST_SUBSHELL] = exec_subshell,
	[AST_AND] = exec_and,
	[AST_OR] = exec_or,
	[AST_PIPELINE] = exec_pipeline
	};

	if (node->status)
		return (node->status);
	handler = handlers[node->type];
	if (!handler)
		return (shell_exit(node->shell), 1);
	return (handler(node));
}
