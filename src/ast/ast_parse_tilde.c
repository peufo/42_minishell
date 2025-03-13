/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_tilde.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:17:40 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/13 21:05:21 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_expendable(t_string *line, char *tilde)
{
	bool	before_ok;
	bool	after_ok;

	if (!tilde)
		return (false);
	before_ok = tilde == line->value || ft_isspace(*(tilde - 1));
	after_ok = *(tilde + 1) == '\0'
		|| ft_isspace(*(tilde + 1))
		|| *(tilde + 1) == '/';
	return (before_ok && after_ok);
}

void	ast_parse_tilde(t_ast *node)
{
	t_string	line;
	char		*tilde;
	char		*home;

	line.value = NULL;
	string_push_str(&line, node->line);
	tilde = ast_tokens_find(line.value, "~");
	if (!tilde)
		return (free(line.value));
	home = env_get(node->shell, "HOME");
	while (tilde)
	{
		if (is_expendable(&line, tilde))
			string_replace(&line, tilde, tilde + 1, home);
		tilde = ast_tokens_find(tilde + 1, "~");
	}
	free(node->line);
	node->line = line.value;
	return ;
}
