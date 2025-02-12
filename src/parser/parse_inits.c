/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:10:08 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/12 08:03:53 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pars_free_ast(t_ast *ast)
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
		pars_free_ast(ast->left);
		ast->left = NULL;
	}
	if (ast->right)
	{
		pars_free_ast(ast->right);
		ast->right = NULL;
	}
	free(ast);
}

t_ast	*pars_init_ast(void)
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
