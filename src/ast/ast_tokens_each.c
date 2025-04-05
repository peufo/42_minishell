/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tokens_each.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:40:59 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/05 14:16:24 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast_state	get_next_state(t_ast_state state, char token)
{
	if (state == AST_STATE_DEFAULT && token == '"')
		return (AST_STATE_DQUOTE);
	if (state == AST_STATE_DEFAULT && token == '\'')
		return (AST_STATE_QUOTE);
	if (state == AST_STATE_DQUOTE && token == '"')
		return (AST_STATE_DEFAULT);
	if (state == AST_STATE_QUOTE && token == '\'')
		return (AST_STATE_DEFAULT);
	return (state);
}

char	*ast_tokens_each(char *line, void *data, int (stop)(char *, void *))
{
	char		*cursor;
	int			in_brackets;
	t_ast_state	state;

	in_brackets = 0;
	cursor = line;
	state = AST_STATE_DEFAULT;
	while (*cursor)
	{
		state = get_next_state(state, *cursor);
		if (state == AST_STATE_DEFAULT)
		{
			if (*cursor == '(')
				in_brackets++;
			else if (*cursor == ')')
				in_brackets--;
			if (!in_brackets && stop(cursor, data))
				break ;
		}
		cursor++;
	}
	if (!*cursor)
		return (NULL);
	return (cursor);
}
