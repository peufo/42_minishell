/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:26:32 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/04 23:40:43 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ast_take_word(t_ast *node, char *cursor)
{
	char	*word;

	lexer(node, cursor);
	if (!node->tokens)
		return (NULL);
	word = ft_strdup(*node->tokens);
	lexer_free(&node->lexer);
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

static int	throw_redir_parse_error(t_ast *node)
{
	node->shell->ast_error = true;
	node->status = 2;
	throw(node, (char *[]){"Redirection syntax error", NULL});
	return (node->status);
}

static t_redir_type	get_redir_type(char *cursor)
{
	if (cursor[0] == '>' && cursor[1] == '>')
		return (REDIR_APPEND);
	if (cursor[0] == '>')
		return (REDIR_OUTPOUT);
	if (cursor[0] == '<' && cursor[1] == '<')
		return (REDIR_HERDOC);
	return (REDIR_INPUT);
}

static void	add_redir(t_ast *node, char *cursor, char *name)
{
	static int	open_flags[] = {
	[REDIR_INPUT] = O_RDONLY,
	[REDIR_HERDOC] = -1,
	[REDIR_APPEND] = O_CREAT | O_WRONLY | O_APPEND,
	[REDIR_OUTPOUT] = O_CREAT | O_WRONLY | O_TRUNC,
	};
	static int	fd_std[] = {
	[REDIR_INPUT] = STDIN_FILENO,
	[REDIR_HERDOC] = STDIN_FILENO,
	[REDIR_APPEND] = STDOUT_FILENO,
	[REDIR_OUTPOUT] = STDOUT_FILENO,
	};
	t_redir		*redir;

	redir = ft_calloc(1, sizeof(*redir));
	if (!redir)
		return (shell_exit(node->shell));
	redir->type = get_redir_type(cursor);
	redir->open_flags = open_flags[redir->type];
	redir->fd_std = fd_std[redir->type];
	redir->name = ast_take_word(node, name);
	if (!redir->name)
		return (free(redir), throw_redir_parse_error(node), (void)0);
	ft_lstadd_back(&node->redir, ft_lstnew(redir));
	return ;
}

static int	pick_redir(t_ast *node)
{
	static char	*tokens[] = {"<", "<<", ">", ">>", NULL};
	char		*cursor;
	int			token_len;
	char		*name;

	if (node->status)
		return (node->status);
	cursor = ast_tokens_find_multi(node->line, tokens);
	while (cursor)
	{
		token_len = 1;
		if (cursor[0] == cursor[1])
			token_len = 2;
		name = cursor + token_len;
		if (!*name)
			return (throw_redir_parse_error(node));
		add_redir(node, cursor, name);
		if (*name == ' ')
			name++;
		delete_chars(cursor, ast_tokens_find(name, " "));
		cursor = ast_tokens_find_multi(cursor, tokens);
	}
	return (0);
}

void	ast_parse_command(t_ast *node)
{
	node->type = AST_COMMAND;
	pick_redir(node);
	ast_parse_tilde(node);
}
