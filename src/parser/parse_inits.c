/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:10:08 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/13 17:49:41 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->args)
	{
		free_2dtab(ast->args);
		ast->args = NULL;
	}
	if (ast->left)
	{
		parse_free_ast(ast->left);
		ast->left = NULL;
	}
	if (ast->right)
	{
		parse_free_ast(ast->right);
		ast->right = NULL;
	}
	free(ast);
}

t_ast	*parse_init_ast(void)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (throw_error("malloc in :", __FILE__, __LINE__), NULL);
	node->left = NULL;
	node->right = NULL;
	node->args = NULL;
	node->op = AST_OP_NULL;
	node->type = AST_END;
	return (node);
}

void	parse_free(t_sh *shell)
{
	parse_free_ast(shell->ast);
	debug(shell, "AST were freed\n");
}
