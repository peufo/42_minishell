/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 06:59:20 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/21 07:06:28 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_dquote(char *line)
{
	int	i;
	int	count;

	i =  0;
	count = 1;
	while (line && line[i])
	{
		if (line[i] == '"')
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (CLOSED);
	return (UNCLOSED);
}

static bool	check_quote(char *line)
{
	int	i;
	int	count;

	i =  0;
	count = 1;
	while (line && line[i])
	{
		if (line[i] == '\'')
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (CLOSED);
	return (UNCLOSED);
}

bool	check_end_in_line(char *line, int state)
{
	if (!line)
		return (false);
	if (state == LEXER_DQUOTE || state == LEXER_VAR_DQUOTE)
		return (check_dquote(line));
	else if (state == LEXER_QUOTE)
		return (check_quote(line));
	return (LINE_IS_COMPLETE);
}
