/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 00:20:00 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/22 11:20:01 by jvoisard         ###   ########.fr       */
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
		node->status = 0;
		node->shell->exit_status = 0;
		errno = false;
		return (true);
	}
	name = redir->name;
	while (*line && *name)
		if (*(line++) != *(name++))
			return (false);
	return (!*line && !*name);
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

static int	heredoc(t_ast *node, t_redir *redir, t_pipe *herepipe)
{
	t_string	doc;

	signal(SIGINT, SIG_DFL);
	close(herepipe->out);
	doc.value = NULL;
	if (redir->type == REDIR_HEREDOC)
		string_push_char(&doc, '"');
	fill_heredoc(node, redir, &doc);
	if (redir->type == REDIR_HEREDOC)
	{
		string_push_char(&doc, '"');
		expand_var(node, &doc);
	}
	ft_putstr_fd(doc.value, herepipe->in);
	close(herepipe->in);
	string_free(&doc);
	shell_exit(node->shell);
	return (node->status);
}

int	exec_redir_heredoc(t_ast *node, t_redir *redir)
{
	t_pipe		herepipe;
	int			pid;

	if (redir->type != REDIR_HEREDOC && redir->type != REDIR_HEREDOC_QUOTED)
		return (0);
	if (redir->fd)
		return (0);
	if (pipe(herepipe.fildes) == -1)
		return (shell_exit(node->shell), 1);
	node->status = 0;
	redir->fd = herepipe.out;
	pid = fork();
	if (pid)
	{
		signal(SIGINT, SIG_IGN);
		close(herepipe.in);
		node->status = waitstatus(node, pid);
		node->shell->exit_status = node->status;
		signal(SIGINT, handle_signal_int);
		if (node->status == 130)
			return (close(herepipe.out), redir->fd = -1, 1);
		return (0);
	}
	return (heredoc(node, redir, &herepipe));
}
