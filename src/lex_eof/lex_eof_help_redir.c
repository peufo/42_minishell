/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_help_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 08:28:40 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/18 06:42:41 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*catch_the_redir_code(char *line)
{
	int		i;
	int		len;
	char	*res;
	char	*tmp;

	i = 0;
	len = 0;
	tmp = ft_strchrstr(line, "<<");
	if (!tmp)
		return (NULL);
	while (ft_isspace(tmp[i]) || tmp[i] == '<')
		i++;
	while (ft_isalnum(tmp[i + len]))
		len++;
	res = ft_calloc(len + 1, sizeof(char));
	len = 0;
	while (ft_isalnum(tmp[i]))
		res[len++] = tmp[i++];
	res[len] = '\0';
	return (res);
}

void	safe_init_redir_array(t_sh *shell, t_input *input)
{
	int		count;
	bool	dquote;
	bool	squote;

	dquote = false;
	squote = false;
	if (input->state == INPUT_DQUOTE)
		dquote = true;
	if (input->state == INPUT_QUOTE)
		squote = true;
	if (input->redir_line)
		count = count_redir_in_line(shell, input->redir_line, dquote, squote);
	else if (input->line)
		count = count_redir_in_line(shell, input->line, dquote, squote);
	input->nb_redir = count;
	if (input->redir_input)
		free(input->redir_input);
	input->redir_input = ft_calloc((count + 1), sizeof(char *));
	if (!input->redir_input)
		return ;
	if (input->redir_code)
		free(input->redir_code);
	input->redir_code = ft_calloc((count + 1), sizeof(char *));
	if (!input->redir_code)
		return (string_array_free(&input->redir_input));
}

void	check_quotes(char c, bool *dquote, bool *quote)
{
	if (c == '"')
	{
		if (*dquote)
			*dquote = false;
		else
			*dquote = true;
	}
	if (c == '\'')
	{
		if (*quote)
			*quote = false;
		else
			*quote = true;
	}
}

static void	suppress_last_line(char **newline, char *line)
{
	int		i;
	int		newlines;
	char	*buf;

	i = 0;
	newlines = 0;
	while (line[i])
		if (line[i++] == '\n')
			newlines++;
	i = 0;
	while (line[i] && newlines > 1)
		if (line[i++] == '\n')
			newlines--;
	newlines = 0;
	buf = ft_calloc(i + 1, 1);
	while (i-- > 0 && line[newlines])
	{
		buf[newlines] = line[newlines];
		newlines++;
	}
	free(*newline);
	*newline = buf;
}

void	checkout_from_redir(t_sh *shell)
{
	int		i;
	char	*line;

	i = 0;
	if (!shell->input.redir_input || !shell->input.redir_input[0])
		return ;
	line = ft_strchr(shell->input.redir_input[0], '\n');
	suppress_last_line(&shell->input.redir_input[0], line);
	while (shell->input.redir_input[i] && ++i < shell->input.nb_redir)
		suppress_last_line(&shell->input.redir_input[i],
			shell->input.redir_input[i]);
}
