/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_stack_commands.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:51:49 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/31 06:07:50 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	stack_to_buffer(char **buffer, char *line)
{
	char	*tmp;
	size_t	tlen;

	if (!line)
		return ;
	tlen = ft_strlen(line) + 2;
	if (buffer && *buffer)
		tlen += ft_strlen(*buffer);
	tmp = ft_calloc(1, tlen + 1);
	if (!tmp)
		return ;
	if (buffer && *buffer)
	{
		ft_strlcat(tmp, *buffer, tlen + 1);
		ft_strlcat(tmp, "\n", tlen + 1);
	}
	ft_strlcat(tmp, line, tlen + 1);
	free(*buffer);
	*buffer = tmp;
}

void	stack_to_history(char *line, t_sh *shell)
{
	(void)line;
	(void)shell;
	errno = false;
}

void	assure_heredoc_line(t_sh *shell)
{
	ft_putstr_fd(">>", 1);
	shell->input.redir_line = get_line(STDIN_FILENO);
	if (g_is_sigint)
		shell->line2 = ft_strdup(shell->input.redir_line);
}

void	assure_eof_line(t_sh *shell)
{
	ft_putstr_fd("> ", 1);
	shell->input.line = get_line(STDIN_FILENO);
	if (g_is_sigint)
		shell->line2 = ft_strdup(shell->input.line);
}
