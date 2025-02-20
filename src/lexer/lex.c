/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:34:52 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/20 08:27:38 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_line(t_sh *shell)
{
	while (*(shell->lexer.cursor) != '\0')
		shell->lexer.cursor++;
}

static bool	next_state_match(t_sh *shell, t_lexer_next_state *next)
{
	if (next->state != shell->lexer.state)
		return (false);
	if (!ft_include(next->charset, *shell->lexer.cursor))
		return (false);
	return (true);
}

static t_lexer_state	get_next_state(t_sh *shell)
{
	t_lexer_next_state			*next;
	static t_lexer_next_state	next_states[] = {
	{LEXER_DEFAULT, "\"", LEXER_DQUOTE},
	{LEXER_DEFAULT, "'", LEXER_QUOTE},
	{LEXER_DEFAULT, "$", LEXER_VAR},
	{LEXER_DEFAULT, CHARSET_META, LEXER_META},
	{LEXER_QUOTE, "'", LEXER_DEFAULT},
	{LEXER_DQUOTE, "\"", LEXER_DEFAULT},
	{LEXER_DQUOTE, "$", LEXER_VAR_DQUOTE},
	{LEXER_VAR, "\"", LEXER_DQUOTE},
	{LEXER_VAR, "'", LEXER_QUOTE},
	{LEXER_VAR, CHARSET_META, LEXER_META},
	{LEXER_VAR_DQUOTE, "\"", LEXER_DEFAULT},
	{LEXER_VAR_DQUOTE, CHARSET_META, LEXER_DQUOTE},
	{0, NULL, 0}
	};

	next = next_states;
	while (next->state)
	{
		if (next_state_match(shell, next))
			return (next->next_state);
		next++;
	}
	return (LEXER_NO_STATE);
}

static void	lex_get_context(t_sh *shell, char **cursor, int state, int next_state)
{
	return ;
	if (!cursor || !*cursor)
		return ;
	printf("Cursor is : %s\n", *cursor);
	printf("Acutal state is : %d\n", state);
	printf("Next state is : %d\n", next_state);
	if (shell->lexer.token.value)
		printf("\nToken is : %s\n\n", shell->lexer.token.value);
	else
		printf("\nNo token in this context\n");
}
/*
static bool	lex_hawk_eye(t_sh *shell, char **str, int state, int next)
{
	if (*str[0] == '"' && *str[1] == '\0' && state == 1 && next == 4)
		return (BONUS_MOD);
	if (*str[0] == '\0')
	return (BASIC_MOD);
}*/

void	lex(t_sh *shell)
{
	t_lexer_state	next_state;

	lex_free(shell);
	shell->lexer.state = LEXER_DEFAULT;
	shell->lexer.cursor = shell->line;
	if (!ft_strlen(shell->lexer.cursor))
		shell_exit(shell);
	lexer_action_skip_blank(shell);
	while (*(shell->lexer.cursor))
	{
		next_state = get_next_state(shell);
		if (*(shell->lexer.cursor) == '#' && next_state <= 1)
			skip_line(shell);
//		if (lex_hawkeye(shell, &shell->lexer.cursor, shell->lexer.state, next_state))
//			return (BONUS_MOD);
		if (next_state)
			lexer_action(shell, next_state);
		else
			lexer_state(shell);
		lex_get_context(shell, &shell->lexer.cursor, shell->lexer.state, next_state);
	}
	lexer_action(shell, LEXER_META);
//	return (BASIC_MOD);
}

void	lex_free(t_sh *shell)
{
	string_free(&shell->lexer.token);
	string_free(&shell->lexer.varname);
	string_array_free(&shell->lexer.tokens);
}
