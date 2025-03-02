/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_subshell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:09:40 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/02 13:45:08 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_parenthesis_open(char *line)
{
	while (ft_isspace(*line))
		line++;
	if (*line != '(')
		return (NULL);
	return (line);
}

static char	*get_parenthesis_close(char *line)
{
	while (*line)
		line++;
	line--;
	while (ft_isspace(*line))
		line--;
	if (*line != ')')
		return (NULL);
	return (line);
}

int	ast_parse_subshell(t_ast *node)
{
	char	*parenthesis_open;
	char	*parenthesis_close;

	parenthesis_open = get_parenthesis_open(node->line);
	parenthesis_close = get_parenthesis_close(node->line);
	if (!parenthesis_open || !parenthesis_close)
		return (false);
	node->type = AST_SUBSHELL;
	node->children = ft_calloc(2, sizeof(*node->children));
	if (!node->children)
		return (shell_exit(node->shell), false);
	node->children[0] = ast_create(
			node->shell,
			ft_strcut(parenthesis_open + 1, parenthesis_close)
			);
	return (true);
}
