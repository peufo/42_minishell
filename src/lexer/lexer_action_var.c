/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_action_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:13:28 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/19 11:11:44 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t = tokens;
	while (*t)
	{
		string_push_str(&node->lexer.token, *(t++));
		if (*t)
		{
			string_array_push(&node->lexer.tokens, node->lexer.token.value);
			node->lexer.token.value = NULL;
		}
	}
	string_array_free(&tokens);
}

static void	expand_no_varname(t_ast *node)
{
	if (*node->lexer.cursor == '?')
		return (expand_exit_status(node));
	if (ft_include("/ \t\n", *(node->lexer.cursor)))
		string_push_str(&node->lexer.token, "$");
	if (!ft_include("/?* \t\n", *(node->lexer.cursor)))
		lexer_action_next_char(node);
}

void	lexer_action_expand_var(t_ast *node)
{
	char	cursor;

	if (!node->lexer.varname.value)
		return (expand_no_varname(node));
	expand_var(node);
	cursor = *(node->lexer.cursor);
	if (!ft_include("?*$/ \t\n", cursor))
		lexer_action_next_char(node);
}

void	lexer_action_expand_var_end_token(t_ast *node)
{
	lexer_action_expand_var(node);
	lexer_action_end_token(node);
}
