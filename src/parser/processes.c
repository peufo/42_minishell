/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:23:37 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/30 12:23:37 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pars_find_next_operator(t_ast *ast)
{
	int		op;
	t_token	*element;
	t_list	*elements;

	if (!ast || !ast->args)
		return ;
	elements = ast->args;
	pars_get_position(ast, elements);
	element = (t_token *)elements->content;
	op = pars_get_op(element->type);
	if (op == AST_OP_NULL)
		ast->type = AST_COMMAND;
	else
		ast->type = pars_get_type(op);
}

void	pars_context_type(t_ast *ast)
{
	(void)ast;
}

void	pars_parse_command(t_ast *ast)
{
	(void)ast;
}
