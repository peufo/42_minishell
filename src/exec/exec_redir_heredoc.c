/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 00:20:00 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/05 17:00:56 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		close(p.in);
		string_free(doc);
		exec_redir_restore_std(node);
		return (throw(node, NULL));
	}
	ft_putstr_fd(doc->value, p.in);
	close(p.in);
	return (0);
}

static void	expand_var(t_ast *node, t_string *doc)
{
	char	**tokens;

	tokens = lexer(node, doc->value);
	if (!tokens)
		return ;
	string_free(doc);
	doc->value = ft_strdup(*tokens);
	string_array_free(&tokens);
	return ;
}

int	exec_redirect_heredoc(t_ast *node, t_redir *redir)
{
	t_string	doc;
	char		*line;

	if (redir->type != REDIR_HEREDOC && redir->type != REDIR_HEREDOC_QUOTED)
		return (0);
	node->status = 0;
	doc.value = NULL;
	if (redir->type == REDIR_HEREDOC)
		string_push_char(&doc, '"');
	while (true)
	{
		line = readline("heredoc> ");
		if (is_heredoc_end(node, redir, line))
			break ;
		string_push_str(&doc, line);
		string_push_char(&doc, '\n');
		free(line);
	}
	if (line)
		free(line);
	if (redir->type == REDIR_HEREDOC)
	{
		string_push_char(&doc, '"');
		expand_var(node, &doc);
	}
	write_heredoc(node, &doc);
	string_free(&doc);
	return (node->status > 1);
}
