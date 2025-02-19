/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:10:56 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/19 09:11:46 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_process_single_quote(t_lexer *lexer)
{
	char	*start;

	if (*lexer->cursor != '\'')
		return ;
	start = ++lexer->cursor;
	while (*lexer->cursor && *lexer->cursor != '\'')
		lexer->cursor++;
	if (*lexer->cursor == '\'')
	{
		lexer_add_token(lexer, TOKEN_WORD, ft_substr(start, 0,
				lexer->cursor - start));
		lexer->cursor++;
	}
	else
		throw_error("Unclosed single quote", __FILE__, __LINE__);
}

void	lexer_process_double_quote(t_lexer *lexer)
{
	char	*start;

	if (*lexer->cursor != '"')
		return ;
	start = ++lexer->cursor;
	while (*lexer->cursor && *lexer->cursor != '"')
	{
		if (*lexer->cursor == '$')
		{
			lexer_add_token(lexer, TOKEN_WORD, ft_cut(start, lexer->cursor));
			lexer_process_variable(lexer);
			start = lexer->cursor;
		}
		else
			lexer->cursor++;
	}
	if (*lexer->cursor == '"')
	{
		if (lexer->cursor > start)
			lexer_add_token(lexer, TOKEN_WORD, ft_cut(start, lexer->cursor));
		lexer->cursor++;
	}
	else
		throw_error("Unclosed double quote", __FILE__, __LINE__);
}

void	lexer_process_variable(t_lexer *lexer)
{
	(void)lexer;
}
