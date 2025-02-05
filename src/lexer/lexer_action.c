/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_action.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:21:54 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/04 18:05:03 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lexer_action_next_char(t_sh *shell)
{
	shell->lexer.cursor++;
}

void	lexer_action_skip_blank(t_sh *shell)
{
	char	**cursor;

	cursor = &shell->lexer.cursor;
	while (**cursor == ' ' || **cursor == '\t' || **cursor == '\n')
		(*cursor)++;
}

void	lexer_action_end_token(t_sh *shell)
{
	if (!shell->lexer.token.value)
		return ;
	ft_lstadd_back(&shell->lexer.tokens, ft_lstnew(shell->lexer.token.value));
	shell->lexer.token.value = NULL;
	lexer_action_skip_blank(shell);
}

void	lexer_action_ensure_token(t_sh *shell)
{
	string_push_str(&shell->lexer.token, "");
	shell->lexer.cursor++;
}

void	lexer_action(t_sh *shell, t_lexer_state next_state)
{
	t_lexer_action_handler			handler;
	static t_lexer_action_handler	handlers[][8] = {
	[LEXER_VAR][LEXER_DQUOTE] = lexer_action_expand_var,
	[LEXER_VAR][LEXER_QUOTE] = lexer_action_expand_var,
	[LEXER_VAR_DQUOTE][LEXER_DQUOTE] = lexer_action_expand_var,
	[LEXER_VAR_DQUOTE][LEXER_DEFAULT] = lexer_action_expand_var,
	[LEXER_DEFAULT][LEXER_QUOTE] = lexer_action_ensure_token,
	[LEXER_DEFAULT][LEXER_DQUOTE] = lexer_action_ensure_token,
	[LEXER_DEFAULT][LEXER_META] = lexer_action_end_token,
	[LEXER_VAR][LEXER_META] = lexer_action_expand_var_end_token,
	};

	handler = handlers[shell->lexer.state][next_state];
	if (!handler)
		handler = lexer_action_next_char;
	handler(shell);
	shell->lexer.state = next_state;
}
