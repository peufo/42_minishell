/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:10:56 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/21 12:18:33 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_eof_process_word(t_sh *shell, t_lexer *lexer)
{
	char	*start;

	start = lexer->cursor;
	while (*lexer->cursor && !ft_isspace(*lexer->cursor) && !ft_strchr("()|><"
			, *lexer->cursor))
		lexer->cursor++;
	string_array_push(&lexer->tokens, ft_cut(start, lexer->cursor));
	(void)shell;
}

void	lex_eof_process_parenthesis(t_sh *shell, t_lexer *lexer)
{
	if (*lexer->cursor == '(')
	{
		string_array_push(&lexer->tokens, "(\0");
		lexer->cursor++;
	}
	else if (*lexer->cursor == ')')
	{
		string_array_push(&lexer->tokens, ")\0");
		lexer->cursor++;
	}
	else
		debug(shell, "\nNOOOOTHING parantheses\n");
}

void	lex_eof_process_redirection(t_sh *shell, t_lexer *lexer)
{
	char	*start;

	start = lexer->cursor;
	if (*lexer->cursor == '>' || *lexer->cursor == '<')
	{
		if (*(lexer->cursor + 1) == *lexer->cursor)
			lexer->cursor += 2;
		else
			lexer->cursor++;
		string_array_push(&lexer->tokens, ft_cut(start, lexer->cursor));
	}
	else
		debug(shell, "\nNOOOOTHING redirection\n");
}

void	lex_eof_process_gate_and_pipe(t_sh *shell, t_lexer *lexer)
{
	if (*lexer->cursor == '|')
	{
		lexer->cursor++;
		if (*lexer->cursor == '|')
		{
			string_array_push(&lexer->tokens, ft_strdup("||"));
			lexer->cursor++;
		}
		else
			string_array_push(&lexer->tokens, ft_strdup("|"));
	}
	else if (*lexer->cursor == '&')
	{
		lexer->cursor++;
		if (*lexer->cursor == '&')
		{
			string_array_push(&lexer->tokens, ft_strdup("&&"));
			lexer->cursor++;
		}
	}
	else
		debug(shell, "\nNOOOOTHING pipe et operateurs\n");
}

void	lex_eof_process_quotes_and_var(t_sh *shell, t_lexer *lexer)
{
	int	state;

	state = shell->lexer.entry_state;
	debug_arr(shell, (char *[]){"\nEntry state is : ", ft_itoa(state), "\n", NULL});
	if (*(lexer->cursor) && (*lexer->cursor == '\'' || state == 3))
		lex_eof_process_single_quote(shell, lexer);
	else if (*lexer->cursor && (*lexer->cursor == '"' || state % 2 == 0))
		lex_eof_process_double_quote(shell, lexer);
	else if (*lexer->cursor == '$')
		lex_eof_process_variable(shell, lexer);
	else if (!ft_isspace(*lexer->cursor) && !ft_strchr("()|><", *lexer->cursor))
		lex_eof_process_word(shell, lexer);
}
