/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_action_var_dquote.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:06:54 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/22 00:49:40 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_var_dquote(t_ast *node)
{
	char	*value;

	value = env_get(node->shell, node->lexer.varname.value);
	string_free(&node->lexer.varname);
	if (value)
		string_push_str(&node->lexer.token, value);
}

static void	expand_no_varname_dquote(t_ast *node)
{
	char	cursor;

	cursor = *(node->lexer.cursor);
	if (cursor == '?')
		return (expand_exit_status(node));
	if (cursor == '"' || cursor == '\''
		|| (ft_include(CHARSET_VAR_END, cursor) && cursor != '*')
		|| ft_include(CHARSET_SPACE, cursor)
		|| ft_include(CHARSET_META, cursor))
		string_push_str(&node->lexer.token, "$");
	if (ft_include("\"*", cursor))
		lexer_action_next_char(node);
}

void	expand_exit_status(t_ast *node)
{
	char	*exit_status;

	exit_status = ft_itoa(node->shell->exit_status);
	string_push_str(&node->lexer.token, exit_status);
	free(exit_status);
	node->lexer.cursor++;
}

void	lexer_action_expand_var_dquote(t_ast *node)
{
	char	cursor;

	if (!node->lexer.varname.value)
		return (expand_no_varname_dquote(node));
	expand_var_dquote(node);
	cursor = *(node->lexer.cursor);
	if (!ft_include(CHARSET_VAR_END, cursor)
		&& !ft_include(CHARSET_META, cursor)
		&& !ft_include(CHARSET_SPACE, cursor)
		&& !ft_include("'", cursor))
		lexer_action_next_char(node);
}
