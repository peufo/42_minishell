/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:26:32 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/17 18:50:47 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ast_take_word(t_ast *node, char *cursor)
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

static int	pick_redir(t_ast *node, char ***files, char *token)
{
	char	*cursor;
	char	*word;
	int		token_len;

	if (node->status)
		return (node->status);
	token_len = ft_strlen(token);
	cursor = ast_tokens_find(node->line, token);
	while (cursor)
	{
		if (!*(cursor + token_len))
			return (throw(node, (char *[]){"parse error", NULL}));
		word = ast_take_word(node, cursor + token_len);
		if (!word)
			return (throw(node, (char *[]){"parse error", NULL}));
		string_array_push(files, word);
		delete_chars(cursor, ast_tokens_find(cursor + token_len + 1, " "));
		cursor = ast_tokens_find(cursor, token);
	}
	return (0);
}
/*
static void	debug_redir_struct(t_redir r)
{
	int	i;

	i = 0;
	printf("\nDEBUG REDIR STRUCT\n");
	while (r.files_in && r.files_in[i])
		printf("Files in : %s\n", r.files_in[i++]);
	i = 0;
	if (r.files_out && r.files_out[i])
		printf("Files out : %s\n", r.files_out[i++]);
	i = 0;
	if (r.files_out_append && r.files_out_append[i])
		printf("Files last append : %s\n", r.files_out_append[i++]);
}*/

void	ast_parse_command(t_ast *node)
{
	char	*last_write;
	char	*last_append;

	node->type = AST_COMMAND;
	ast_parse_heredoc(node);
	last_write = ast_tokens_find_last(node->line, ">");
	last_append = ast_tokens_find_last(node->line, ">>");
	node->redir.is_last_append = (last_append && last_append >= last_write - 1);
	pick_redir(node, &node->redir.files_out_append, ">>");
	pick_redir(node, &node->redir.files_out, ">");
	pick_redir(node, &node->redir.files_in, "<");
	ast_parse_tilde(node);
	ast_parse_wildcard(node);
}
