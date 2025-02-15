/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:10:08 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/15 13:41:51 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_free_ast(t_ast **ast)
{
	if (!*ast)
		return ;
	if ((*ast)->args)
		string_array_free(&(*ast)->args);
	if ((*ast)->left)
		parse_free_ast(&(*ast)->left);
	if ((*ast)->right)
		parse_free_ast(&(*ast)->right);
	free(*ast);
	*ast = NULL;
}

t_ast	*parse_init_ast(void)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (throw_error("malloc in :", __FILE__, __LINE__), NULL);
	node->left = NULL;
	node->right = NULL;
	ft_bzero(&node->args, sizeof(char *));
	node->op = AST_OP_NULL;
	node->type = AST_END;
	return (node);
}

void	parse_free(t_sh *shell)
{
	parse_free_ast(&shell->ast);
	debug(shell, "AST were freed\n");
}
