/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:26:32 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/12 14:09:45 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*take_word(t_ast *node, char *cursor)
{
	char	*word;

	lex(node, cursor);
	if (!node->tokens)
		return (NULL);
	word = ft_strdup(*node->tokens);
	lex_free(&node->lexer);
	string_array_free(&node->tokens);
	return (word);
}

static void	delete_chars(char *from, char *to)
{
	if (!to)
	{
		to = from;
		while (*to)
			to++;
	}
	while (*to)
		*(from++) = *(to++);
	while (from <= to)
		*(from++) = '\0';
}

static void	pick_redir(t_ast *node, char ***files, char *token)
{
	char	*cursor;
	char	*word;
	int		token_len;

	token_len = ft_strlen(token);
	cursor = ast_tokens_find(node->line, token);
	while (cursor)
	{
		if (!*(cursor + token_len))
			return (throw_error("parse error", __FILE__, __LINE__));
		word = take_word(node, cursor + token_len);
		if (!word)
			return (throw_error("parse error", __FILE__, __LINE__));
		string_array_push(files, word);
		delete_chars(cursor, ast_tokens_find(cursor + token_len + 1, " "));
		cursor = ast_tokens_find(cursor, token);
	}
}

// TODO: find if last is ">" or ">>"
void	ast_parse_command(t_ast *node)
{
	char	*last_write;
	char	*last_append;

	node->type = AST_COMMAND;
	last_write = ast_tokens_find_last(node->line, ">");
	last_append = ast_tokens_find_last(node->line, ">>");
	node->redir.is_last_append = last_append && last_append >= last_write - 1;
	pick_redir(node, &node->redir.files_out_append, ">>");
	pick_redir(node, &node->redir.files_out, ">");
	pick_redir(node, &node->redir.files_in, "<");
}
