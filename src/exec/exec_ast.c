/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:08:17 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/19 05:48:37 by dyodlm           ###   ########.fr       */
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
