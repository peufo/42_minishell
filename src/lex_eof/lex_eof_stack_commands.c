/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_stack_commands.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:51:49 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/03 07:07:35 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quotes(char c, bool *dquote, bool *quote)
{
	if (c == '"')
		*dquote = !(*dquote);
	if (c == '\'')
		*quote = !(*quote);
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
	if (!g_is_sigint)
		shell->input.redir_line = readline("heredoc>");
	else
		shell->input.redir_line = readline("BackToShell>");
	if (g_is_sigint)
		shell->line2 = ft_strdup(shell->input.redir_line);
}

void	assure_eof_line(t_sh *shell)
{
	shell->input.line = readline(">");
	if (g_is_sigint)
		shell->line2 = ft_strdup(shell->input.line);
}
