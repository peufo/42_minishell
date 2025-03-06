/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_subshell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:09:40 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/06 10:43:00 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_bracket_open(char *line)
{
	while (ft_isspace(*line))
		line++;
	if (*line != '(')
		return (NULL);
	return (line);
}

static char	*get_bracket_close(char *line)
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
	char	*bracket_open;
	char	*bracket_close;

	bracket_open = get_bracket_open(node->line);
	bracket_close = get_bracket_close(node->line);
	if (!bracket_open || !bracket_close)
		return (false);
	node->type = AST_SUBSHELL;
	node->children = ft_calloc(2, sizeof(*node->children));
	if (!node->children)
		return (shell_exit(node->shell), false);
	node->children[0] = ast_create(
			node->shell,
			ft_strcut(bracket_open + 1, bracket_close)
			);
	return (true);
}
