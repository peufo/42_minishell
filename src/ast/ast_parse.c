/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 01:11:30 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/25 18:59:43 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ast_parse_cut_by(
	t_ast *node,
	char *token,
	t_atype type
)
{
	char	*cursor;
	t_ast	**children;

	cursor = ast_tokens_find(node->line, token);
	if (!cursor)
		return (false);
	children = ft_calloc(3, sizeof(*children));
	if (!children)
		return (shell_exit(node->shell), false);
	children[0] = ast_create(
			node->shell,
			ft_strcut(node->line, cursor)
			);
	children[1] = ast_create(
			node->shell,
			ft_strcut(cursor + ft_strlen(token), NULL)
			);
	node->children = children;
	node->type = type;
	return (true);
}

void	ast_parse(t_ast *node)
{
	if (ast_parse_cut_by(node, "||", AST_OR))
		return ;
	if (ast_parse_cut_by(node, "&&", AST_AND))
		return ;
	if (ast_parse_pipe(node))
		return ;
	if (ast_parse_subshell(node))
		return ;
	node->type = AST_COMMAND;
	return ;
}
