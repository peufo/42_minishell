/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 00:20:00 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/06 12:51:33 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_heredoc_end(t_ast *node, t_redir *redir, char *line)
{
	char	*name;

	if (!line)
	{
		node->is_herdoc = true;
		throw(node, (char *[]){
			"warning: heredoc delimited by end-of-file (wanted `",
			redir->name,
			"')",
			NULL});
		node->is_herdoc = false;
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

static int	heredoc_to_fd(t_ast *node, t_string *doc)
{
	t_pipe	herepipe;

	if (pipe(herepipe.fildes) == -1)
	{
		string_free(doc);
		shell_exit(node->shell);
		return (-1);
	}
	ft_putstr_fd(doc->value, herepipe.in);
	close(herepipe.in);
	return (herepipe.out);
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

static void	fill_heredoc(t_ast *node, t_redir *redir, t_string *doc)
{
	char	*line;
	char	*prompt;

	prompt = ft_strcat_arr((char *[]){"herdoc(", redir->name, ")> ", NULL});
	while (true)
	{
		line = readline(prompt);
		if (is_heredoc_end(node, redir, line))
			break ;
		string_push_str(doc, line);
		string_push_char(doc, '\n');
		free(line);
	}
	free(prompt);
	if (line)
		free(line);
}

int	exec_redir_heredoc(t_ast *node, t_redir *redir)
{
	t_string	doc;

	if (redir->type != REDIR_HEREDOC && redir->type != REDIR_HEREDOC_QUOTED)
		return (0);
	if (redir->fd)
		return (0);
	node->status = 0;
	doc.value = NULL;
	if (redir->type == REDIR_HEREDOC)
		string_push_char(&doc, '"');
	fill_heredoc(node, redir, &doc);
	if (redir->type == REDIR_HEREDOC)
	{
		string_push_char(&doc, '"');
		expand_var(node, &doc);
	}
	redir->fd = heredoc_to_fd(node, &doc);
	string_free(&doc);
	return (node->status > 1);
}
