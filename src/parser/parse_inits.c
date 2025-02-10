/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:10:08 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/10 15:10:09 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pars_free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->args)
		free_2dtab(ast->args);
	if (ast->left)
		pars_free_ast(ast->left);
	if (ast->right)
		pars_free_ast(ast->right);
}

t_ast	*pars_init_ast(void)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (throw_error("malloc in :", __FILE__, __LINE__), NULL);
	node->left = malloc(sizeof(t_ast));
	if (!(node)->left)
		return (pars_free_ast(node),
			throw_error("malloc in :", __FILE__, __LINE__), NULL);
	node->right = malloc(sizeof(t_ast));
	if (!(node)->right)
		return (pars_free_ast(node),
			throw_error("malloc in :", __FILE__, __LINE__), NULL);
	return (node);
}
