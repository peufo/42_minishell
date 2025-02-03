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

int	pars_find_next_operator(t_ast *ast)
{
	int		op;
	t_token	*element;
	t_list	*elements;

	if (!ast || !ast->args)
		return (-1);
	elements = ast->args;
	ast->cursor = pars_get_position(ast, elements);
	element = (t_token *)elements->content;
	op = pars_get_op(element->type);
	if (op == AST_OP_NULL)
		ast->type = AST_COMMAND;
	else
		ast->type = pars_get_type(op);
	return (ast->cursor);
}

void	pars_split_lr(t_ast *ast, t_ast *left, t_ast *right)
{
	int		index;
	t_list	*ast_node;

	left->args = NULL;
	right->args = NULL;
	while (ast_node)
	{
		if (index < ast->cursor)
			ft_lstadd_back(&(left->args), ft_lstnew(ast_node->content));
		else if (index > ast->cursor)
			ft_lstadd_back(&(right->args), ft_lstnew(ast_node->content));
		ast_node = ast_node->next;
		index++;
	}
}

void	pars_parse_command(t_ast *ast)
{
	(void)ast;
}
