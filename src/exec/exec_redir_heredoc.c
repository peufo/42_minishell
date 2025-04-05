/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 00:20:00 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/05 13:55:53 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	get_is_quoted(char *name)
{
	while (*name)
		if (*(name++) == '\'')
			return (true);
	return (false);
}

static void	rm_quote(char *name)
{
	char	*read;

	read = name;
	while (*read)
	{
		while (*read == '\'' || *read == '"')
			read++;
		*(name++) = *read;
		if (*read)
			read++;
	}
}

static bool	is_heredoc_end(t_ast *node, t_redir *redir, char *line)
{
	char	*name;

	if (!line)
	{
		throw(node, (char *[]){
			"warning: heredoc delimited by end-of-file (wanted `",
			redir->name,
			"')",
			NULL});
		return (true);
	}
	if (g_is_sigint)
	{
		node->status = 130;
		node->shell->exit_status = node->status;
		return (true);
	}
	name = redir->name;
	while (*line && *name)
		if (*(line++) != *(name++))
			return (false);
	return (!*line && !*name);
}

static int	write_heredoc(t_ast *node, t_string *doc)
{
	t_pipe	p;

	if (node->shell->exit_status)
		return (node->shell->exit_status);
	exec_redir_save_std(node, STDIN_FILENO);
	if (pipe(p.fildes) == -1)
	{
		string_free(doc);
		exec_redir_restore_std(node);
		shell_exit(node->shell);
		return (1);
	}
	if (dup2(p.out, STDIN_FILENO) == -1 || close(p.out) == -1)
	{
		string_free(doc);
		exec_redir_restore_std(node);
		return (throw(node, NULL));
	}
	ft_putstr_fd(doc->value, p.in);
	close(p.in);
	return (0);
}

// if !is_quoted, double quote "doc" and run lexer
// once write doc on redirected STD_IN
int	exec_redirect_heredoc(t_ast *node, t_redir *redir)
{
	bool		is_quoted;
	t_string	doc;
	char		*line;

	if (redir->type != REDIR_HEREDOC)
		return (0);
	node->status = 0;
	doc.value = NULL;
	is_quoted = get_is_quoted(redir->name);
	if (!is_quoted)
		string_push_char(&doc, '"');
	rm_quote(redir->name);
	while (true)
	{
		line = readline("heredoc> ");
		if (is_heredoc_end(node, redir, line))
			break;
		string_push_str(&doc, line);
		string_push_char(&doc, '\n');
	}
	if (!is_quoted)
		string_push_char(&doc, '"');
	return (write_heredoc(node, &doc) > 1);
}
