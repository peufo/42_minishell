/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:30:25 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/05 12:47:19 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*ast_create(t_sh *shell, char *line)
{
	t_ast	*node;

	if (!line)
		return (NULL);
	node = ft_calloc(1, sizeof(*node));
	if (!node)
		return (shell_exit(shell), NULL);
	node->shell = shell;
	node->line = line;
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
	string_array_free(&(*node)->files_in);
	string_array_free(&(*node)->files_out);
	string_array_free(&(*node)->tokens);
	lex_free(&(*node)->lexer);
	if ((*node)->pipes)
	{
		free((*node)->pipes);
		(*node)->pipes = NULL;
	}
	free((*node)->line);
	(*node)->line = NULL;
	free(*node);
	*node = NULL;
}
