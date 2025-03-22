/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_stack_commands.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:51:49 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/22 06:38:30 by dyodlm           ###   ########.fr       */
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

static void	store_history(t_sh *shell, char *line)
{
	(void)shell;
	(void)line;
}

void	stack_to_history(char *line, t_sh *shell)
{
	store_history(shell, line);
	errno = false;
}
