/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_action_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:13:28 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/05 15:08:14 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_end_with_space(char *value)
{
	if (!*value)
		return (false);
	while (*value)
		value++;
	value--;
	return (ft_include(" \t\n", *value));
}

static void	expand_var(t_lexer *lexer)
{
	char	*value;
	char	**tokens;
	char	**t;

	value = env_get(lexer->node->shell, lexer->varname.value);
	string_free(&lexer->varname);
	if (!value)
		return ;
	tokens = ft_split(value, ' ');
	if (!tokens)
		shell_exit(lexer->node->shell);
	if (ft_include(" \t\n", *value))
		lexer_action_end_token(lexer);
	t = tokens;
	while (*t)
	{
		string_push_str(&lexer->token, *t);
		lexer_action_var_catch_wild(lexer, ft_strlen(*(t++)));
		if (*t)
			lexer_action_end_token(lexer);
	}
	if (is_end_with_space(value))
		lexer_action_end_token(lexer);
	string_array_free(&tokens);
}

static void	expand_no_varname(t_lexer *lexer)
{
	char	cursor;

	cursor = *(lexer->cursor);
	if (cursor == '?')
		return (lexer_expand_exit_status(lexer));
	if (cursor != '*' && (
			ft_include(CHARSET_VAR_END, cursor)
			|| ft_include(CHARSET_SPACE, cursor)
		))
		string_push_str(&lexer->token, "$");
	if (cursor == '*'
		|| !ft_include(CHARSET_VAR_END, cursor))
	{
		lexer_action_next_char(lexer);
	}
}

void	lexer_action_expand_var(t_lexer *lexer)
{
	char	cursor;

	if (!lexer->varname.value)
		return (expand_no_varname(lexer));
	expand_var(lexer);
	cursor = *(lexer->cursor);
	if (!ft_include(CHARSET_VAR_END, cursor)
		&& !ft_include(CHARSET_SPACE, cursor))
		lexer_action_next_char(lexer);
}

void	lexer_action_expand_var_end_token(t_lexer *lexer)
{
	lexer_action_expand_var(lexer);
	lexer_action_end_token(lexer);
}
