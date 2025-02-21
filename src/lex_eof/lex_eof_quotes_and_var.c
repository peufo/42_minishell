/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_quotes_and_var.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 07:39:17 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/21 10:22:49 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_var(t_sh *shell, t_lexer *lexer)
{
	int			i;

	i = 0;
	(void)i;
	(void)shell;
	(void)lexer;
	return (NULL);
}

void	lex_eof_process_variable(t_sh *shell, t_lexer *lexer)
{
	char	*cursor;
	char	*var;

	return ;
	var = extract_var(shell, lexer);
	if (!var)
		return ;
	cursor = lexer->cursor;
	while (*cursor)
	{
		if (*cursor == '$')
			continue ;
	}
}


void	lex_eof_process_single_quote(t_sh *shell, t_lexer *lexer)
{
	char	*start;

	if (*lexer->cursor != '\'' && shell->lexer.entry_state % 2 != 1)
		return ;
	start = ++lexer->cursor;
	if (shell->lexer.entry_state == 1)
		start--;
	while (*lexer->cursor && *lexer->cursor != '\'')
		lexer->cursor++;
	if (*lexer->cursor == '\'')
	{
		string_array_push(&lexer->tokens, ft_cut(start, lexer->cursor));
		lexer->cursor++;
		shell->lexer.entry_state = LEXER_DEFAULT;
	}
	else
		shell->lexer.entry_state = LEXER_QUOTE;
}

void	lex_eof_process_double_quote(t_sh *shell, t_lexer *lexer)
{
	char	*st;

	if (*lexer->cursor != '"' && (shell->lexer.entry_state % 2 != 0 || shell->lexer.entry_state == 1))
		return ;
	st = ++lexer->cursor;
	if (shell->lexer.entry_state != 1)
		st--;
	while (*lexer->cursor && *lexer->cursor != '"')
	{
		if (*lexer->cursor == '$')
		{
			string_array_push(&lexer->tokens, ft_cut(st, lexer->cursor));
			lex_eof_process_variable(shell, lexer);
			st = lexer->cursor;
			shell->lexer.entry_state = LEXER_DEFAULT;
		}
		else
			lexer->cursor++;
	}
	if (*lexer->cursor == '"')
	{
		if (lexer->cursor > st)
			string_array_push(&lexer->tokens, ft_cut(st, lexer->cursor));
		lexer->cursor++;
		shell->lexer.entry_state = LEXER_DEFAULT;
	}
	else
		shell->lexer.entry_state = LEXER_DQUOTE;
}
