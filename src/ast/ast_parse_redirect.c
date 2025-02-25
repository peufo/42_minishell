/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 22:44:18 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/25 00:37:51 by jvoisard         ###   ########.fr       */
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
	int	files_count;

	ast_redirect_pick(node, &node->files_in, "<");
	ast_redirect_pick(node, &node->files_out, ">");
	files_count = string_array_len(node->files_in);
	if (files_count)
	{
		node->fildes_in = ft_calloc(files_count, sizeof(*node->fildes_in));
		if (!node->fildes_in)
			return ((void)shell_exit(node->shell));
	}
	files_count = string_array_len(node->files_out);
	if (files_count)
	{
		node->fildes_out = ft_calloc(files_count, sizeof(*node->fildes_out));
		if (!node->fildes_out)
			return ((void)shell_exit(node->shell));
	}
}