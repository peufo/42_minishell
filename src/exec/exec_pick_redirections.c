/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pick_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:57:59 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/25 18:18:16 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*pick_file(char *cursor)
{
	char	*start;

	while (*cursor == ' ')
		cursor++;
	start = cursor;
	while (*cursor != ' ')
		cursor++;
	return (ft_strcut(start, cursor));
}

static	void	delete_redirection(char *cursor)
{
	char	*write;
	char	*read;

	write = cursor;
	read = cursor + 1;
	while (*read == ' ')
		read++;
	while (*read != ' ')
		read++;
	while (*read)
		*(write++) = *(read++);
	*write = '\0';
}

void	exec_pick_redirections(t_ast *node, char ***files, char *token)
{
	char	*cursor;

	cursor = ast_tokens_find(node->line, token);
	while (cursor)
	{
		if (!*(cursor + 1))
			return (throw_error("parse error", __FILE__, __LINE__));
		string_array_push(files, pick_file(cursor + 1));
		delete_redirection(cursor);
		cursor = ast_tokens_find(cursor, token);
	}
}
