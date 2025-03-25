/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_action_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:13:28 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/25 15:00:11 by jvoisard         ###   ########.fr       */
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

static void	catch_var_wilds(t_ast *node, int var_len)
{
	char	*token;

	token = node->lexer.token.value;
	if (!token)
		return ;
	while (*token)
		token++;
	token -= var_len;
	if (token < node->lexer.token.value)
		return ;
	while (*token)
	{
		if (*token == '*')
			string_array_push(&node->lexer.wilds, token);
		token++;
	}
}

static void	expand_var(t_ast *node)
{
	char	*value;
	char	**tokens;
	char	**t;

	value = env_get(node->shell, node->lexer.varname.value);
	string_free(&node->lexer.varname);
	if (!value)
		return ;
	tokens = ft_split(value, ' ');
	if (!tokens)
		shell_exit(node->shell);
	if (ft_include(" \t\n", *value))
		lexer_action_end_token(node);
	t = tokens;
	while (*t)
	{
		string_push_str(&node->lexer.token, *t);
		catch_var_wilds(node, ft_strlen(*(t++)));
		if (*t)
			lexer_action_end_token(node);
	}
	if (is_end_with_space(value))
		lexer_action_end_token(node);
	string_array_free(&tokens);
}

static void	expand_no_varname(t_ast *node)
{
	char	cursor;

	cursor = *(node->lexer.cursor);
	if (cursor == '?')
		return (expand_exit_status(node));
	if (cursor != '*' && (
			ft_include(CHARSET_VAR_END, cursor)
			|| ft_include(CHARSET_SPACE, cursor)
		))
		string_push_str(&node->lexer.token, "$");
	if (cursor == '*'
		|| !ft_include(CHARSET_VAR_END, cursor))
	{
		lexer_action_next_char(node);
	}
}

void	lexer_action_expand_var(t_ast *node)
{
	char	cursor;

	if (!node->lexer.varname.value)
		return (expand_no_varname(node));
	expand_var(node);
	cursor = *(node->lexer.cursor);
	if (!ft_include(CHARSET_VAR_END, cursor)
		&& !ft_include(CHARSET_SPACE, cursor))
		lexer_action_next_char(node);
}

void	lexer_action_expand_var_end_token(t_ast *node)
{
	lexer_action_expand_var(node);
	lexer_action_end_token(node);
}
