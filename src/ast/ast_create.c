/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:30:25 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/19 08:08:31 by dyodlm           ###   ########.fr       */
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

static void	ast_free_redir(t_ast **node)
{
	string_array_free(&(*node)->redir.files_in);
	string_array_free(&(*node)->redir.files_out);
	string_array_free(&(*node)->redir.files_out_append);
}

static void	ast_free_heredoc(t_ast **node)
{
	if ((*node)->heredoc.files_in)
		unlink(*(*node)->heredoc.files_in);
	string_array_free(&(*node)->heredoc.files_in);
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
	ast_free_heredoc(node);
	ast_free_redir(node);
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
