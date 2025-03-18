/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_action_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:13:28 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/18 15:53:35 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_var(t_ast *node)
{
	char	*value;

	value = env_get(node->shell, node->lexer.varname.value);
	string_free(&node->lexer.varname);
	if (value)
		string_push_str(&node->lexer.token, value);
}

static void	expand_exit_status(t_ast *node)
{
	char	*exit_status;

	exit_status = ft_itoa(node->shell->exit_status);
	string_push_str(&node->lexer.token, exit_status);
	free(exit_status);
	node->lexer.cursor++;
}

static void	expand_no_varname(t_ast *node)
{
	if (*node->lexer.cursor == '?')
		return (expand_exit_status(node));
	if (node->lexer.state == LEXER_VAR)
	{
		if (ft_include(" \t\n", *(node->lexer.cursor)))
			string_push_str(&node->lexer.token, "$");
		if (!ft_include("?* \t\n", *(node->lexer.cursor)))
			lexer_action_next_char(node);
	}
	if (node->lexer.state == LEXER_VAR_DQUOTE)
	{
		if (ft_include("\" \t\n", *(node->lexer.cursor)))
			string_push_str(&node->lexer.token, "$");
		if (!ft_include("'?* \t\n", *(node->lexer.cursor)))
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
	if (node->lexer.state == LEXER_VAR)
	{
		if (!ft_include("?*$/ \t\n", cursor))
			lexer_action_next_char(node);
	}
	if (node->lexer.state == LEXER_VAR_DQUOTE)
	{
		if (!ft_include("'?* \t\n", cursor))
			lexer_action_next_char(node);
	}
}

void	lexer_action_expand_var_end_token(t_ast *node)
{
	lexer_action_expand_var(node);
	lexer_action_end_token(node);
}
