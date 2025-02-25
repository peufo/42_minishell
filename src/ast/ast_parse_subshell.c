/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_subshell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:09:40 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/25 18:22:51 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ast_parse_subshell(t_ast *node)
{
	char	*line;

	line = node->line;
	if (*line != '(')
		return (false);
	while (*line)
		line++;
	line--;
	if (*line != ')')
		return (false);
	node->type = AST_SUBSHELL;
	node->children = ft_calloc(2, sizeof(*node->children));
	if (!node->children)
		return (shell_exit(node->shell), false);
	node->children[0] = ast_create(
			node->shell,
			ft_strcut(node->line + 1, line)
			);
	return (true);
}
