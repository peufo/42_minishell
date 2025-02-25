/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:40:59 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/25 18:57:36 by jvoisard         ###   ########.fr       */
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

char	*ast_tokens_find(char *line, char *token)
{
	char		*cursor;
	int			in_parenthesis;
	t_ast_state	state;

	in_parenthesis = 0;
	cursor = line;
	state = AST_STATE_DEFAULT;
	while (*cursor)
	{
		state = get_next_state(state, *cursor);
		if (state == AST_STATE_DEFAULT)
		{
			if (*cursor == '(')
				in_parenthesis++;
			else if (*cursor == ')')
				in_parenthesis--;
			if (!in_parenthesis && ft_startwith(cursor, token))
				break ;
		}
		cursor++;
	}
	if (!*cursor)
		return (NULL);
	return (cursor);
}
