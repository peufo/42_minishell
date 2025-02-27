/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 06:59:20 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/27 10:28:28 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_dquote(t_input *input)
{
	(void)input;
	return (CLOSED);
}

static bool	check_quote(t_input *input)
{
	(void)input;
	return (CLOSED);
}

bool	check_end_in_line(t_input *input)
{
	char	*cursor;

	cursor = input->stack;
	if (!cursor)
		return (false);
	if ((input->state == LEXER_DQUOTE || input->state == LEXER_VAR_DQUOTE))
	{
		if (*cursor == '"')
			return (LINE_IS_COMPLETE);
		return (check_dquote(input));
	}
	else if (input->state == LEXER_QUOTE)
	{
		if (*cursor == '\'')
			return (LINE_IS_COMPLETE);
		return (check_quote(input));
	}
	return (LINE_IS_COMPLETE);
}
