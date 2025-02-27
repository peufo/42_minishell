/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:10:56 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/25 04:48:47 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_eof_process_word(t_sh *shell, t_lexer *lexer)
{
	char	*start;

	start = lexer->cursor;
	while (*lexer->cursor && !ft_isspace(*lexer->cursor) && !ft_strchr("()|><"
			, *lexer->cursor) && shell)
		lexer->cursor++;
	string_array_push(&lexer->tokens, ft_cut(start, lexer->cursor));
}

void	lex_eof_process_parenthesis(t_sh *shell, t_lexer *lexer)
{
	if (*lexer->cursor == '(' && shell)
	{
		string_array_push(&lexer->tokens, "(\0");
		lexer->cursor++;
	}
	else if (*lexer->cursor == ')')
	{
		string_array_push(&lexer->tokens, ")\0");
		lexer->cursor++;
	}
}

void	lex_eof_process_redirection(t_sh *shell, t_lexer *lexer)
{
	char	*start;

	start = lexer->cursor;
	if ((*lexer->cursor == '>' || *lexer->cursor == '<') && shell)
	{
		if (*(lexer->cursor + 1) == *lexer->cursor)
			lexer->cursor += 2;
		else
			lexer->cursor++;
		string_array_push(&lexer->tokens, ft_cut(start, lexer->cursor));
	}
}

void	lex_eof_process_gate_and_pipe(t_sh *shell, t_lexer *lexer)
{
	char	*start;
	char	*str;

	if (*lexer->cursor == '|' && shell)
	{
		debug(shell, "got a pipe\n");
		start = lexer->cursor++;
		if (*lexer->cursor == '|')
		{
			lexer->cursor++;
			str = ft_cut(start, lexer->cursor);
			string_array_push(&lexer->tokens, str);
		}
		else
			string_array_push(&lexer->tokens, ft_cut(start, lexer->cursor));
	}
	else if (*lexer->cursor == '&')
	{
		debug(shell, "got an and\n");
		start = lexer->cursor++;
		if (*lexer->cursor == '&')
		{
			lexer->cursor++;
			string_array_push(&lexer->tokens, ft_cut(start, lexer->cursor));
		}
	}
}

void	lex_eof_process_quotes_and_var(t_sh *shell, t_lexer *lexer)
{
	int	state;

	debug_arr(shell, (char *[]){"State in process is ", ft_itoa(shell->lexer.entry_state), "\n", NULL});
	state = shell->lexer.entry_state;
	if (*(lexer->cursor) && (*lexer->cursor == '\'' || (state == LEXER_QUOTE
				&& lex_eof_get_last_type(shell) != 3)))
		lex_eof_process_single_quote(shell, lexer);
	else if (*lexer->cursor && (*lexer->cursor == '"' || ((state == 4
					|| state == 6) && lex_eof_get_last_type(shell) != 4)))
		lex_eof_process_double_quote(shell, lexer);
	else if (*lexer->cursor == '$')
		lex_eof_process_variable(shell, lexer);
	else if (!ft_isspace(*lexer->cursor) && !ft_strchr("()|><", *lexer->cursor))
		lex_eof_process_word(shell, lexer);
	else
		debug(shell, "Nothing in quotes\n");
	debug(shell, "\n");
	if (lexer->token.value)
		debug(shell, lexer->token.value);
	debug(shell, "\n");
}
