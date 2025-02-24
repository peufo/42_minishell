/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 06:59:20 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/24 15:16:13 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_dquote(char *line, int state)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	printf("state : %d\n", state);
	if (state % 2 == 0)
		count += 1;
	while (line && line[i])
	{
		if (line[i] == '"')
			count++;
		i++;
	}
	if (count % 2 == 0 && count != 0)
		return (CLOSED);
	return (UNCLOSED);
}

static bool	check_quote(char *line, int state)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (state == 3)
		count += 1;
	while (line && line[i])
	{
		if (line[i] == '\'')
			count++;
		i++;
	}
	if (count % 2 == 0 && count != 0)
		return (CLOSED);
	return (UNCLOSED);
}

bool	check_end_in_line(char *line, int state, int type)
{
	if (!line)
		return (false);
	if (state == LEXER_DQUOTE || state == LEXER_VAR_DQUOTE)
	{
		if (*line == '"')
			return (LINE_IS_COMPLETE);
		printf("line computed with check dquote\n");
		return (check_dquote(line, state));
	}
	else if (state == LEXER_QUOTE && type != 3)
	{
		if (*line == '\'')
			return (LINE_IS_COMPLETE);
	//	printf("line computed with check quote\n");
		return (check_quote(line, state));
	}
	printf("line is complete\n");
	return (LINE_IS_COMPLETE);
}
