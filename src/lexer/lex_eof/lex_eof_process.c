/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:10:56 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/19 11:09:26 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_parenthesis(t_sh *shell, t_lexer *lexer)
{
	if (*lexer->cursor == '(')
	{
		string_array_push(&shell->lexer.tokens, "(\0");
		lexer->cursor++;
	}
	else if (*lexer->cursor == ')')
	{
		string_array_push(&shell->lexer.tokens, ")\0");
		lexer->cursor++;
	}
}

static void	process_redirection(t_sh *shell, t_lexer *lexer)
{
	char	*start;

	start = lexer->cursor;
	if (*lexer->cursor == '>' || *lexer->cursor == '<')
	{
		if (*(lexer->cursor + 1) == *lexer->cursor)
			lexer->cursor += 2;
		else
			lexer->cursor++;
		string_array_push(&shell->lexer.tokens, ft_cut(start, lexer->cursor));
	}
}

static void	process_gate_and_pipe(t_sh *shell, t_lexer *lexer)
{
	if (*lexer->cursor == '|')
	{
		lexer->cursor++;
		if (*lexer->cursor == '|')
		{
			string_array_push(&shell->lexer.tokens, "||\0");
			lexer->cursor++;
		}
		else
			string_array_push(&shell->lexer.tokens, "|\0");
	}
	else if (*lexer->cursor == '&')
	{
		lexer->cursor++;
		if (*lexer->cursor == '&')
		{
			string_array_push(&shell->lexer.tokens, "&&\0");
			lexer->cursor++;
		}
	}
}

static void	process_quotes_and_var(t_lexer *lexer)
{
	if (*lexer->cursor == '\'')
	{
		lexer_process_single_quote(lexer);
	}
	else if (*lexer->cursor == '"')
	{
		lexer_process_double_quote(lexer);
	}
	else if (*lexer->cursor == '$')
		lexer_process_variable(lexer);
	else if (!ft_isspace(*lexer->cursor) && !ft_strchr("()|><", *lexer->cursor))
		lexer_process_word(lexer);
}
