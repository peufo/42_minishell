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
/*
int	pars_find_next_operator(t_sh *shell)
{
	int		index;
	t_list	*node;
	t_token	*token;

	debug(shell, "FINDING NEXT OPERATOR\n");
	index = 0;
	node = shell->ast;
	while (node)
	{
		token = (t_token *)node->content;
		if (token)
			shell->ast.op = pars_get_op(token->type, shell);
		if (shell->ast.op != AST_OP_NULL)
			return (index);
		node = node->next;
		index++;
	}
	return (-1);
}

void	pars_split_lr(t_ast *left, t_ast *right, t_sh *shell)
{
	int		index;
	t_list	*ast_node;

	debug(shell, "SPLITING LEFT AND RIGHT");
	index = 0;
	left->args = NULL;
	right->args = NULL;
	ast_node = shell->ast.args;
	while (ast_node && index < shell->ast.cursor)
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
*/
void	pars_parse_command(t_sh *shell)
{
	(void)shell;
}
