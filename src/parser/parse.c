/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:24:16 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/30 17:36:49 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_free(t_sh *shell)
{
	(void)shell;
}
/*
static void	pars_split_and_node(t_ast *ast, t_sh *shell, t_list **stack)
{
	pars_split_lr(ast, ast->left, ast->right);
	debug_arr(shell, (char *[]){
		"ast_type -> [",
		ft_itoa(ast->type),
		"]\nfor token indexed at -> [",
		ft_itoa(ast->cursor)
	});
	debug(shell, "]\n");
	ft_lstadd_front(stack, ft_lstnew(ast->right));
	ft_lstadd_front(stack, ft_lstnew(ast->left));
}

static int	pars_process_tokens(t_ast *data, t_sh *shell)
{
	t_list	*stack;
	t_list	*node;
	t_ast	*ast;

	debug(shell, "PROCESSING TOKENS");
	stack = NULL;
	ft_lstadd_front(&stack, ft_lstnew(data));
	while (stack)
	{
		node = stack;
		ast = (t_ast *)node->content;
		stack = stack->next;
		free(node);
		ast->cursor = pars_find_next_operator(ast);
		if (ast->cursor == -1)
			ast->type = AST_COMMAND;
		ast->left->args = NULL;
		ast->right->args = NULL;
		ast->left->left = NULL;
		ast->right->right = NULL;
		ast->right->left = NULL;
		ast->left->right = NULL;
		pars_split_and_node(ast, shell, &stack);
	}
	return (0);
}

static void	debug_tokens(t_sh *shell)
{
	t_list	*current;
	t_token	*token;

	current = shell->lexer.tokens;
	debug(shell, "\nTokens received:\n");
	while (current)
	{
		token = (t_token *)current->content;
		if (token && token->value)
		{
			debug_arr(shell, (char *[]){
				"[",
				token->type,
				"] -> ",
				token->value,
				"\n",
				NULL
			});
		}
		else
			printf("- [NULL or invalid token]\n");
		current = current->next;
	}
}*/

static void	debug_tokens(t_sh *shell)
{
	(void)shell;
}

void	parse(t_sh *shell)
{
	return ;
	if (!shell)
		return (throw_error("No tokens received", __FILE__, __LINE__));
	debug_tokens(shell);
	shell->ast.left = NULL;
	shell->ast.right = NULL;
	if (ft_lstsize(shell->ast.args) == 1)
		return (throw_error("WTF", __FILE__, __LINE__));
}
/*	pars_process_tokens(&shell->ast, shell);
}*/
