/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:07:24 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/24 23:56:34 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ast_debug_type(t_ast *node)
{
	static char	*types[] = {
	[AST_NULL] = "AST_NULL",
	[AST_COMMAND] = "AST_COMMAND",
	[AST_SUBSHELL] = "AST_SUBSHELL",
	[AST_AND] = "AST_AND",
	[AST_OR] = "AST_OR",
	[AST_PIPELINE] = "AST_PIPELINE"
	};

	return (types[node->type]);
}

static void	ast_debug_tokens(t_ast *node)
{
	char	**tokens;

	tokens = node->tokens;
	debug(node->shell, "[\"");
	debug(node->shell, *(tokens++));
	debug(node->shell, "\"");
	while (*tokens)
	{
		debug(node->shell, ", \"");
		debug(node->shell, *(tokens++));
		debug(node->shell, "\"");
	}
	debug(node->shell, "]");
}

static void	ast_debug_children(t_ast *node, int deep)
{
	t_ast	**children;

	children = node->children;
	while (children && *children)
		ast_debug(*(children++), deep + 1);
}

static void	ast_debug_files(t_ast *node, char **files)
{
	if (!files || !*files)
	{
		debug(node->shell, "()");
		return ;
	}
	debug(node->shell, "(");
	debug(node->shell, *(files++));
	while (*files)
	{
		debug(node->shell, ", ");
		debug(node->shell, *(files++));
	}
	debug(node->shell, ")");
}

void	ast_debug(t_ast *node, int deep)
{
	int		i;

	i = 0;
	while (i < deep)
	{
		debug(node->shell, "\t");
		i++;
	}
	debug(node->shell, ast_debug_type(node));
	debug(node->shell, " ");
	ast_debug_files(node, node->files_in);
	debug(node->shell, "->");
	ast_debug_tokens(node);
	debug(node->shell, "->");
	ast_debug_files(node, node->files_out);
	debug(node->shell, "\n");
	ast_debug_children(node, deep);
}
