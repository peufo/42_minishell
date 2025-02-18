/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_quotes_checker.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:10:56 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/18 09:03:33 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	lex_check_var(t_sh *shell, char *line, char **buffer)
{
	(void)shell;
	(void)line;
	(void)buffer;
	return (false);
}

static int	count_squotes(char *line)
{
	int	count;

	count = 0;
	(void)line;
	return (count);
}

static int	count_dquotes(char *line)
{
	int	count;

	count = 0;
	(void)line;
	return (count);
}

bool	lex_check_quotes(t_sh *shell, char *line, char **buffer)
{
	while (*line)
	{
		if (*line == '"' && (*line == '\n' || !*line))
			return (true);
	}
	return (false);
}
