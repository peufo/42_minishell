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
	if (shell->ast.types)
	{
		free(shell->ast.types);
		shell->ast.types = NULL;
		debug(shell, "types freed\n");
	}
	debug(shell, "parse was freed\n");
}
/*
static void	pars_split_and_node(t_sh *shell, t_list **stack)
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

static int	pars_process_tokens(t_sh *shell)
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
}*/

static void	debug_tokens(t_sh *shell)
{
	int			i;
	int			j;
	int			type;
	static char	*names[] = {
		"PAR_OPEN", "PAR_CLOSED", "LESS", "DLESS", "DGREAT",
		"GREAT", "AND", "OR", "PIPELINE", "WORD"
	};

	j = 0;
	while (shell->ast.types[j] != -1)
	{
		i = 0;
		type = shell->ast.types[i++];
		debug_arr(shell, (char *[]){
			"token type is : ",
			names[type],
			"\n",
			NULL
		});
		j++;
	}
}

static void	type_tokens(t_sh *shell)
{
	int	i;

	i = 0;
	while (shell->lex.toks[i])
		i++;
	shell->ast.types = malloc((i + 1) * sizeof(int));
	if (!shell->ast.types)
		return (throw_error("Transfer of tokens failed in :",
				__FILE__, __LINE__));
	i = 0;
	while (shell->lex.toks[i])
	{
		shell->ast.types[i] = pars_get_type(shell, shell->lex.toks[i]);
		i++;
	}
	shell->ast.types[i] = -1;
}

void	parse(t_sh *shell)
{
	if (!shell->lex.toks)
		return (throw_error("No tokens received", __FILE__, __LINE__));
	type_tokens(shell);
	debug_tokens(shell);
	return (lex_free(shell));
	shell->ast.toks = shell->lex.toks;
	shell->ast.left = NULL;
	shell->ast.right = NULL;
	parse_free(shell);
	return (debug(shell, "hello"));
}
/*	if (ft_lstsize(shell->ast.args) == 1)
		return (throw_error("WTF", __FILE__, __LINE__));
	pars_process_tokens(&shell->ast, shell);
}*/
