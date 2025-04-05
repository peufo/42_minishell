/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_action_var_dquote.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:06:54 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/05 15:09:22 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_var_dquote(t_lexer *lexer)
{
	char	*value;

	value = env_get(lexer->node->shell, lexer->varname.value);
	string_free(&lexer->varname);
	if (value)
		string_push_str(&lexer->token, value);
}

static void	expand_no_varname_dquote(t_lexer *lexer)
{
	char	cursor;

	cursor = *(lexer->cursor);
	if (cursor == '?')
		return (lexer_expand_exit_status(lexer));
	if (cursor == '"' || cursor == '\''
		|| (ft_include(CHARSET_VAR_END, cursor) && cursor != '*')
		|| ft_include(CHARSET_SPACE, cursor)
		|| ft_include(CHARSET_META, cursor))
		string_push_str(&lexer->token, "$");
	if (ft_include("\"*", cursor))
		lexer_action_next_char(lexer);
}

void	lexer_expand_exit_status(t_lexer *lexer)
{
	char	*exit_status;

	exit_status = ft_itoa(lexer->node->shell->exit_status);
	string_push_str(&lexer->token, exit_status);
	free(exit_status);
	lexer->cursor++;
}

void	lexer_action_expand_var_dquote(t_lexer *lexer)
{
	char	cursor;

	if (!lexer->varname.value)
		return (expand_no_varname_dquote(lexer));
	expand_var_dquote(lexer);
	cursor = *(lexer->cursor);
	if (!ft_include(CHARSET_VAR_END, cursor)
		&& !ft_include(CHARSET_META, cursor)
		&& !ft_include(CHARSET_SPACE, cursor)
		&& !ft_include("'", cursor))
		lexer_action_next_char(lexer);
}
