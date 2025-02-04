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
#include "limits.h"

static void	process_parenthesis(t_lexer *lexer, t_sh *shell)
{
	debug(shell, "\n INTO PROCESS PAR \n");
	if (*lexer->cursor == '(')
	{
		lexer_add_token(lexer, TOKEN_PAR_OPEN, "(", shell);
		lexer->cursor++;
	}
	else if (*lexer->cursor == ')')
	{
		lexer_add_token(lexer, TOKEN_PAR_CLOSE, ")", shell);
		lexer->cursor++;
	}
}

static void	process_redirection(t_lexer *lexer, t_sh *shell)
{
	char	*start;

	debug(shell, "\n INTO PROCESS REDIRECTION \n");
	start = lexer->cursor;
	if (*lexer->cursor == '>' || *lexer->cursor == '<')
	{
		if (*(lexer->cursor + 1) == *lexer->cursor)
			lexer->cursor += 2;
		else
			lexer->cursor++;
		lexer_add_token(lexer, TOKEN_GROUP_REDIRECT,
			ft_cut(start, lexer->cursor), shell);
	}
}

static void	process_gate_and_pipe(t_lexer *lexer, t_sh *shell)
{
	if (*lexer->cursor == '|')
	{
		lexer->cursor++;
		if (*lexer->cursor == '|')
		{
			lexer_add_token(lexer, TOKEN_OR, "||", shell);
			lexer->cursor++;
		}
		else
			lexer_add_token(lexer, TOKEN_PIPELINE, "|", shell);
	}
	else if (*lexer->cursor == '&')
	{
		lexer->cursor++;
		if (*lexer->cursor == '&')
		{
			lexer_add_token(lexer, TOKEN_AND, "&&", shell);
			lexer->cursor++;
		}
	}
}

static void	process_quotes_and_var(t_lexer *lexer, t_sh *shell)
{
	debug(shell, "\n INTO PROCESS QUOTES AND VAR \n");
	if (*lexer->cursor == '\'')
	{
		lexer_process_single_quote(lexer, shell);
	}
	else if (*lexer->cursor == '"')
	{
		lexer_process_double_quote(lexer, shell);
	}
	else if (*lexer->cursor == '$')
		lexer_process_variable(lexer, shell);
	else if (!ft_isspace(*lexer->cursor) && !ft_strchr("()|><", *lexer->cursor))
		lexer_process_word(lexer, shell);
}

void	lex(t_sh *shell)
{
	t_lexer	lexer;

	debug(shell, "\n INTO MAIN LEXER \n");
	ft_memset(&lexer, 0, sizeof(t_lexer));
	shell->lexer.nbt = 0;
	lexer.cursor = shell->line;
	if (!check_string(lexer.cursor))
		return (lex_free(shell));
	while (*lexer.cursor)
	{
		lexer_skip_whitespace(&lexer, shell);
		lexer_skip_comment(&lexer, shell);
		process_parenthesis(&lexer, shell);
		process_redirection(&lexer, shell);
		process_gate_and_pipe(&lexer, shell);
		process_quotes_and_var(&lexer, shell);
	}
}
