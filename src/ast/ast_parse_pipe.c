/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:32:31 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/25 16:45:54 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_pipes_count(char *line)
{
	char	*token_pipe;
	int		pipes_count;

	token_pipe = ast_tokens_find(line, "|");
	pipes_count = 0;
	while (token_pipe)
	{
		pipes_count++;
		token_pipe = ast_tokens_find(token_pipe + 1, "|");
	}
	return (pipes_count);
}

int	ast_parse_pipe(t_ast *node)
{
	char	*token_start;
	char	*token_end;
	int		pipes_count;
	t_ast	**children;
	int		i;

	pipes_count = get_pipes_count(node->line);
	if (!pipes_count)
		return (false);
	node->type = AST_PIPELINE;
	node->children = ft_calloc(pipes_count + 2, sizeof(*children));
	if (!node->children)
		return (shell_exit(node->shell), false);
	i = 0;
	token_start = node->line;
	while (i <= pipes_count)
	{
		token_end = ast_tokens_find(token_start, "|");
		node->children[i++] = ast_create(
				node->shell,
				ft_strcut(token_start, token_end)
				);
		token_start = token_end + 1;
	}
	return (true);
}
