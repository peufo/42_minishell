/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:10:08 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/22 22:23:36 by jvoisard         ###   ########.fr       */
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

t_ast	*parse_init_ast(t_sh *shell)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
	{
		throw_error("malloc failed in :", __FILE__, __LINE__);
		shell_exit(shell);
		return (NULL);
	}
	node->shell = shell;
	return (node);
}

void	parse_free(t_sh *shell)
{
	parse_free_ast(&shell->ast);
	free(shell->ast);
	shell->ast = NULL;
	debug(shell, "AST were freed\n");
}
