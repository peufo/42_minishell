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
	int		index;
	t_list	*node;
	t_token	*token;

	index = 0;
	node = ast->args;
	while (node)
	{
		token = (t_token *)node->content;
		if (token)
			ast->op = pars_get_op(token->type);
		if (ast->op != AST_OP_NULL)
			return (index);
		node = node->next;
		index++;
	}
	return (-1);
}

void	pars_split_lr(t_ast *ast, t_ast *left, t_ast *right)
{
	int		index;
	t_list	*ast_node;

	index = 0;
	left->args = NULL;
	right->args = NULL;
	ast_node = ast->args;
	while (ast_node && index < ast->cursor)
	{
		ft_lstadd_back(&left->args, ft_lstnew(ast_node->content));
		ast_node = ast_node->next;
		index++;
	}
	if (ast_node)
		ast_node = ast_node->next;
	while (ast_node)
	{
		ft_lstadd_back(&right->args, ft_lstnew(ast_node->content));
		ast_node = ast_node->next;
	}
}

void	pars_parse_command(t_ast *ast)
{
	(void)ast;
}
