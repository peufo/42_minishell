/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_subshell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:09:40 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/23 17:02:13 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ast_parse_subshell(t_ast *node)
{
	char	**tokens;

	tokens = node->tokens;
	if (ft_strcmp(*tokens, "("))
		return (false);
	while (*tokens)
		tokens++;
	tokens--;
	if (ft_strcmp(*tokens, ")"))
		return (false);
	node->type = AST_SUBSHELL;
	node->children = ft_calloc(1, sizeof(*node->children));
	if (!node->children)
		return (shell_exit(node->shell), false);
	node->children[0] = ast_create(
			node->shell,
			string_array_slice(node->tokens + 1, tokens)
			);
	return (true);
}
