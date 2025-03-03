/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pick_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:57:59 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/03 16:14:51 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pick_redirections(t_ast *node, char ***files, char *token)
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
