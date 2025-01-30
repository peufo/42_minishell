/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:34:52 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/30 15:38:18 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_parenthesis(t_lexer *lexer)
{
	if (*lexer->cursor == '(')
	{
		lexer_add_token(lexer, TOKEN_PAR_OPEN, "(");
		lexer->cursor++;
	}
	else if (*lexer->cursor == ')')
	{
		lexer_add_token(lexer, TOKEN_PAR_CLOSE, ")");
		lexer->cursor++;
	}
}

static void	process_redirection(t_lexer *lexer)
{
	char	*start;

	start = lexer->cursor;
	if (*lexer->cursor == '>' || *lexer->cursor == '<')
	{
		if (*(lexer->cursor + 1) == *lexer->cursor)
			lexer->cursor += 2;
		else
			lexer->cursor++;
		lexer_add_token(lexer, TOKEN_GROUP_REDIRECT,
			ft_cut(start, lexer->cursor));
	}
}

static void	process_gate_and_pipe(t_lexer *lexer)
{
	if (*lexer->cursor == '|')
	{
		lexer->cursor++;
		if (*lexer->cursor == '|')
		{
			lexer_add_token(lexer, TOKEN_OR, "||");
			lexer->cursor++;
		}
		else
			lexer_add_token(lexer, TOKEN_PIPELINE, "|");
	}
	else if (*lexer->cursor == '&')
	{
		lexer->cursor++;
		if (*lexer->cursor == '&')
		{
			lexer_add_token(lexer, TOKEN_AND, "&&");
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

void	lex(t_sh *shell)
{
	t_lexer	lexer;

	ft_memset(&lexer, 0, sizeof(t_lexer));
	lexer.cursor = shell->line;
	lexer.tokens = NULL;
	if (!check_string(lexer.cursor))
		return ;
	while (*lexer.cursor)
	{
		lexer_skip_whitespace(&lexer);
		lexer_skip_comment(&lexer);
		process_parenthesis(&lexer);
		process_redirection(&lexer);
		process_gate_and_pipe(&lexer);
		process_quotes_and_var(&lexer);
	}
	shell->lexer.tokens = lexer.tokens;
}
