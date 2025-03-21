/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_help_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 08:28:40 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/22 06:39:09 by dyodlm           ###   ########.fr       */
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

	count = 0;
	dquote = input->state == INPUT_DQUOTE;
	squote = input->state == INPUT_QUOTE;
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

static void	vladimir_poutin(int *a, int *b)
{
	*a = 0;
	*b = 0;
}

static void	suppress_last_line(char **newline, char *line)
{
	t_utils	u;
	char	*buf;

	ft_bzero(&u, sizeof(t_utils));
	while (line[u.i])
		if (line[u.i++] == '\n')
			u.x++;
	while (line[u.j] && u.x > 0)
		if (line[u.j++] == '\n')
			u.x--;
	buf = ft_calloc(u.j, 1);
	vladimir_poutin(&u.i, &u.x);
	while (--u.j > 0 && *line)
	{
		buf[u.i++] = *line;
		line++;
		if (*line == '\n')
		{
			u.x++;
			if (u.x % 2 == 0)
				line++;
		}
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
	line++;
	suppress_last_line(&shell->input.redir_input[0], line);
	while (shell->input.redir_input[i] && i < shell->input.nb_redir)
	{
		suppress_last_line(&shell->input.redir_input[i],
			shell->input.redir_input[i]);
		i++;
	}
}
