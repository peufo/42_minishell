/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 01:11:30 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/23 18:43:57 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ast_parse_cut_by(
	t_ast *node,
	char *token,
	t_atype type
)
{
	char	**token_and;
	t_ast	**children;

	token_and = ast_tokens_find(node->tokens, token);
	if (!token_and)
		return (false);
	children = ft_calloc(3, sizeof(*children));
	if (!children)
		return (shell_exit(node->shell), false);
	children[0] = ast_create(
			node->shell,
			string_array_slice(node->tokens, token_and)
			);
	children[1] = ast_create(
			node->shell,
			string_array_slice(token_and + 1, NULL)
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
	if (ast_parse_cut_by(node, ">", AST_GREAT))
		return ;
	if (ast_parse_cut_by(node, ">>", AST_DGREAT))
		return ;
	if (ast_parse_cut_by(node, "<", AST_LESS))
		return ;
	if (ast_parse_cut_by(node, "<<", AST_DLESS))
		return ;
	if (ast_parse_subshell(node))
		return ;
	node->type = AST_COMMAND;
	return ;
}
