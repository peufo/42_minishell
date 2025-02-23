/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:30:25 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/23 17:02:01 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*ast_create(t_sh *shell, char **tokens)
{
	t_ast	*node;

	if (!tokens)
		return (NULL);
	node = ft_calloc(1, sizeof(*node));
	if (!node)
		return (shell_exit(shell), NULL);
	node->shell = shell;
	node->tokens = tokens;
	ast_parse(node);
	return (node);
}

void	ast_free(t_ast **node)
{
	t_ast	**children;

	if (!*node)
		return ;
	children = (*node)->children;
	if (children)
	{
		while (*children)
			ast_free(children++);
		free((*node)->children);
		(*node)->children = NULL;
	}
	string_array_free(&(*node)->tokens);
	free(*node);
	*node = NULL;
}
