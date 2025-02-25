/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:08:17 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/24 23:55:54 by jvoisard         ###   ########.fr       */
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

	handler = handlers[node->type];
	if (!handler)
		return (throw_error("No handler found ", __FILE__, __LINE__), 0);
	return (handler(node));
}
