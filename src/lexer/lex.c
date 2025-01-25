/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:34:52 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/22 15:07:39 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static t_lexer_state	get_next_state(t_sh *shell)
{
	static t_lexer_state	next_stats[][256] = {
	[LEXER_DEFAULT]['"'] = LEXER_DQUOTE,
	[LEXER_DEFAULT]['\''] = LEXER_QUOTE,
	[LEXER_DEFAULT]['$'] = LEXER_VAR,
	[LEXER_DEFAULT][' '] = LEXER_DEFAULT,
	[LEXER_DEFAULT]['\t'] = LEXER_DEFAULT,
	[LEXER_DEFAULT]['\n'] = LEXER_DEFAULT,
	[LEXER_QUOTE]['\''] = LEXER_DEFAULT,
	[LEXER_DQUOTE]['"'] = LEXER_DEFAULT,
	[LEXER_DQUOTE]['$'] = LEXER_VAR_DQUOTE,
	[LEXER_VAR_DQUOTE]['"'] = LEXER_DEFAULT,
	[LEXER_VAR_DQUOTE][' '] = LEXER_DQUOTE,
	[LEXER_VAR_DQUOTE]['\t'] = LEXER_DQUOTE,
	[LEXER_VAR]['"'] = LEXER_DQUOTE,
	[LEXER_VAR]['\''] = LEXER_QUOTE,
	[LEXER_VAR][' '] = LEXER_DEFAULT,
	[LEXER_VAR]['\t'] = LEXER_DEFAULT,
	[LEXER_VAR]['\n'] = LEXER_DEFAULT,
	[LEXER_VAR]['#'] = LEXER_IGNORE
	};

	return (next_stats[shell->lexer.state][(int)*(shell->lexer.cursor)]);
}

static void	handle_state_quote(t_sh *shell)
{
	string_push(&shell->lexer.token, *shell->lexer.cursor);
	shell->lexer.cursor++;
}

void	lexer_state(t_sh *shell)
{
	t_lexer_state_handler			handler;
	static t_lexer_state_handler	handlers[] = {
	[L_QUOTE] = handle_state_quote,
	[L_VAR] = lexer_state_var,
	[L_VAR_DQUOTE] = lexer_state_var_dquote,
	};

	handler = handlers[shell->lexer.state];
	if (handler)
		handler(shell);
}

void	lexer_state_var(t_sh *shell)
{
	string_push(&shell->lexer.token, *shell->lexer.cursor);
	shell->lexer.cursor++;
}*/
/*
void	lex(t_sh *shell)
{
	t_lexer_state	next_state;

	lex_free(shell);
	shell->lexer.state = L_INIT;
	shell->lexer.cursor = shell->line;
	lexer_transition(shell, L_DEFAULT);
	while (*(shell->lexer.cursor))
	{
		if (!get_next_state1(shell))
			get_next_state2(shell);
		if (next_state)
			lexer_transition(shell, next_state);
		else
			lexer_state(shell);
	}
	lexer_transition(shell, L_DEFAULT);
}*/

void 	tokenise_comment(t_sh *shell)
{
	while (*shell->lexer.cursor)
		*shell->lexer.cursor += 1;
}

int		check_input_errors(t_sh *shell)
{
	(void)shell;
	return (OK);
}

int 	lex(t_sh *shell)
{
	int		state;

	lex_free(shell);
	shell->lexer.cursor = shell->line;
	state = check_input_errors(shell);
	if (state != OK)
		return (message(state, LEX), 0);
	while (*(shell->lexer.cursor))
	{
		state = get_char_state(shell);
		if (state == -1)
			return (message(404, LEX), 0);
		if (state == L_QUOTE || state == L_DQUOTE)
			tokenise_quotes(shell);
		if (state == AND_GATE || state == OR_GATE)
			tokenise_gates(shell);
		if (state == L_PAR_OPEN || state == L_PAR_CLOSE)
			tokenise_parenthesis(shell);
		if (state == L_RDIR || L_LDIR)
			tokenise_redirection(shell);
		if (state == L_IGNORE)
			tokenise_comment(shell);
		shell->lexer.cursor++;
	}
	return (1);
}

void	lex_free(t_sh *shell)
{
	t_token 	*token;
	t_list		*current;
	t_list 		*next;

	current = shell->lexer.tokens;
	while (current)
	{
		token = (t_token *)current->content;
		if (token)
		{
			string_free(&token->value);
			free(token);
		}
		next = current->next;
		free(current);
		current = next;
	}
	shell->lexer.tokens = NULL;
	string_free(&shell->lexer.varname);
	shell->lexer.token.value.value = NULL;
	shell->lexer.token.type = 0;
}
