/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 22:44:18 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/24 23:48:41 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ast_redirect_pick(t_ast *node, char ***files, char *token)
{
	char	**cursor;

	cursor = string_array_find_match(node->tokens, token);
	while (cursor)
	{
		if (!*(cursor + 1))
			return (throw_error("parse error", __FILE__, __LINE__));
		string_array_push(files, ft_strdup(*(cursor + 1)));
		string_array_delete(node->tokens, *cursor);
		string_array_delete(node->tokens, *cursor);
		cursor = string_array_find_match(cursor, token);
	}
}

void	ast_parse_redirect(t_ast *node)
{
	ast_redirect_pick(node, &node->files_out, ">");
	ast_redirect_pick(node, &node->files_in, "<");
}