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

static void	pars_split_and_node(t_ast *ast, t_ast *ast_element, t_sh *shell)
{
	pars_split_lr(ast_element, ast_element->left, ast_element->right);
	debug_arr(shell, (char *[]){
		"ast_type -> [",
		ft_itoa(ast->type),
		"]\nfor token indexed at -> [",
		ft_itoa(ast->cursor)
	});
	debug(shell, "]\n");
	ft_lstaddfront(&ast_element, ft_lstnew(ast_element->right));
	ft_lstaddfront(&ast_element, ft_lstnew(ast_element->left));
}

static int	pars_process_tokens(t_ast *ast, t_sh *shell)
{
	t_list	*tokens;
	t_ast	*ast_element;

	tokens = NULL;
	ft_lstadd_front(&tokens, ft_lstnew(ast));
	while (tokens)
	{
		ast_element = (t_ast *)tokens->content;
		ft_lstremove_front(&tokens);
		ast->cursor = pars_find_next_operator(ast);
		if (ast->cursor == -1)
			ast_element->type = AST_COMMAND;
		ast_element->type = pars_get_type(ast->op);
		ast_element->left = malloc(sizeof(t_ast));
		if (!ast_element->left)
			return (throw_error("malloc in :", __FILE__, __LINE__), 0);
		ast_element->right = malloc(sizeof(t_ast));
		if (!ast_element->right)
			return (throw_error("malloc in :", __FILE__, __LINE__), 0);
		pars_split_and_node(ast, ast_element, shell);
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
}

void	parse(t_sh *shell)
{
	if (!shell || !shell->lexer.tokens)
		return (throw_error("No tokens received", __FILE__, __LINE__));
	debug_tokens(shell);
	shell->ast.args = shell->lexer.tokens;
	shell->ast.left = NULL;
	shell->ast.right = NULL;
	if (ft_lstsize(shell->ast.args) == 1)
		return (throw_error("WTF", __FILE__, __LINE__));
	pars_process_tokens(&shell->ast, shell);
}
