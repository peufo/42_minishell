/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_quotes_and_var.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 07:39:17 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/19 11:42:05 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
char	*extract_var(t_sh *shell, char *cursor, int start)
{
	int			i;

	i = 0;
	(void)i;
	(void)shell;
	(void)cursor;
	(void)start;
	return (NULL);
}

void	lex_check_var(t_sh *shell, char *line, char **buffer, int start)
{
	char	*cursor;
	char	*var;

	(void)buffer;
	var = extract_var(shell, line, start);
	if (!var)
		return ;
	cursor = line;
	while (*cursor)
	{
		if (*cursor == '$')
			continue ;
	}
}*/


void	lex_eof_process_single_quote(t_sh *shell, t_lexer *lexer)
{
	char	*start;

	if (*lexer->cursor != '\'')
		return ;
	start = ++lexer->cursor;
	while (*lexer->cursor && *lexer->cursor != '\'')
		lexer->cursor++;
	if (*lexer->cursor == '\'')
	{
		string_array_push(&shell->lexer.tokens,
				ft_cut(start, lexer->cursor - start));
		lexer->cursor++;
	}
	else
		throw_error("Unclosed single quote", __FILE__, __LINE__);
}

void	lex_eof_process_double_quote(t_sh *shell, t_lexer *lexer)
{
	char	*st;

	if (*lexer->cursor != '"')
		return ;
	st = ++lexer->cursor;
	while (*lexer->cursor && *lexer->cursor != '"')
	{
		if (*lexer->cursor == '$')
		{
			string_array_push(&shell->lexer.tokens, ft_cut(st, lexer->cursor));
			lexer_process_variable(lexer);
			st = lexer->cursor;
		}
		else
			lexer->cursor++;
	}
	if (*lexer->cursor == '"')
	{
		if (lexer->cursor > st)
			string_array_push(&shell->lexer.tokens, ft_cut(st, lexer->cursor));
		lexer->cursor++;
	}
	else
		throw_error("Unclosed double quote", __FILE__, __LINE__);
}
