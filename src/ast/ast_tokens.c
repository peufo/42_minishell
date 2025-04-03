/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:40:59 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/12 12:51:46 by jvoisard         ###   ########.fr       */
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

char	*ast_tokens_find_last(char *line, char *token)
{
	char	*cursor;
	char	*last_result;

	cursor = ast_tokens_find(line, token);
	last_result = cursor;
	while (cursor && *cursor)
	{
		cursor = ast_tokens_find(cursor + 1, token);
		if (!cursor || !*cursor)
			return (last_result);
		last_result = cursor;
	}
	return (last_result);
}

char	*ast_tokens_find(char *line, char *token)
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
			if (!in_brackets && ft_startwith(cursor, token))
				break ;
		}
		cursor++;
	}
	if (!*cursor)
		return (NULL);
	return (cursor);
}
