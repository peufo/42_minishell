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

static void	process_parenthesis(t_sh *shell)
{
	debug(shell, "\n INTO PROCESS PAR \n");
	if (*shell->lex.cursor == '(')
	{
		lexer_add_token(TOKEN_PAR_OPEN, "(", shell);
		shell->lex.cursor++;
	}
	else if (*shell->lex.cursor == ')')
	{
		lexer_add_token(TOKEN_PAR_CLOSE, ")", shell);
		shell->lex.cursor++;
	}
}

static void	process_redirection(t_sh *shell)
{
	char	*start;

	debug(shell, "\n INTO PROCESS REDIRECTION \n");
	start = shell->lex.cursor;
	if (*shell->lex.cursor == '>' || *shell->lex.cursor == '<')
	{
		if (*(shell->lex.cursor + 1) == *shell->lex.cursor)
			shell->lex.cursor += 2;
		else
			shell->lex.cursor++;
		lexer_add_token(TOKEN_GROUP_REDIRECT,
			ft_cut(start, shell->lex.cursor), shell);
	}
}

static void	process_gate_and_pipe(t_sh *shell)
{
	if (*shell->lex.cursor == '|')
	{
		shell->lex.cursor++;
		if (*shell->lex.cursor == '|')
		{
			lexer_add_token(TOKEN_OR, "||", shell);
			shell->lex.cursor++;
		}
		else
			lexer_add_token(TOKEN_PIPELINE, "|", shell);
	}
	else if (*shell->lex.cursor == '&')
	{
		shell->lex.cursor++;
		if (*shell->lex.cursor == '&')
		{
			lexer_add_token(TOKEN_AND, "&&", shell);
			shell->lex.cursor++;
		}
	}
}

static void	process_quotes_and_var(t_sh *shell)
{
	debug(shell, "\n INTO PROCESS QUOTES AND VAR \n");
	if (*shell->lex.cursor == '\'')
	{
		lexer_process_single_quote(shell);
	}
	else if (*shell->lex.cursor == '"')
	{
		lexer_process_double_quote(shell);
	}
	else if (*shell->lex.cursor == '$')
		lexer_process_variable(shell);
	else if (!ft_isspace(*shell->lex.cursor) && !ft_strchr("()|><",
			*shell->lex.cursor))
		lexer_process_word(shell);
}

void	lex(t_sh *shell)
{
	debug(shell, "\n INTO MAIN LEXER \n");
	shell->lex.nbt = 0;
	shell->lex.cursor = shell->line;
	if (!check_string(shell->lex.cursor))
		return (lex_free(shell));
	while (*shell->lex.cursor)
	{
		lexer_skip_whitespace(shell);
		lexer_skip_comment(shell);
		process_parenthesis(shell);
		process_redirection(shell);
		process_gate_and_pipe(shell);
		process_quotes_and_var(shell);
	}
}
