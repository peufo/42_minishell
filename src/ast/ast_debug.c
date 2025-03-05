/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:07:24 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/05 12:51:17 by jvoisard         ###   ########.fr       */
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

static void	ast_debug_children(t_ast *node, int deep)
{
	t_ast	**children;

	children = node->children;
	while (children && *children)
		ast_debug(*(children++), deep + 1);
}

static void	ast_debug_files(char **files)
{
	if (!files || !*files)
	{
		DEBUG("()");
		return ;
	}
	DEBUG("(%s", *(files++));
	while (*files)
	{
		DEBUG(", %s", *(files++));
	}
	DEBUG(")");
}

static void	ast_debug_line(t_ast *node)
{
	char	*line;
	char	*cursor;

	line = ft_strdup(node->line);
	if (!line)
		return ;
	cursor = line;
	while (*cursor)
		cursor++;
	cursor--;
	if (*cursor == '\n')
		*cursor = '\0';
	DEBUG("->[%s]->", line);
	free(line);
}

void	ast_debug(t_ast *node, int deep)
{
	int		i;

	i = 0;
	while (i < deep)
	{
		DEBUG("\t");
		i++;
	}
	DEBUG("%s ", ast_debug_type(node));
	ast_debug_files(node->files_in);
	ast_debug_line(node);
	ast_debug_files(node->files_out);
	DEBUG("\n");
	ast_debug_children(node, deep);
}
