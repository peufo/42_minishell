/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_sentinels.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:41:11 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/28 08:06:07 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	did_pipe_sentinel_see(char *line, bool in_eof)
{
	if (!line[0] || line[0] != '|')
		return (false);
	if (line[1] == '|')
	{
		line++;
		return (!is_token_valid(line, "||", in_eof));
	}
	return (!is_token_valid(line, "|", in_eof));
}

bool	did_less_sentinel_see(char *line, bool in_eof)
{
	int	i;

	i = 1;
	(void)in_eof;
	if (!line[0] || line[0] != '<')
		return (false);
	if (line[1] == '<')
	{
		line++;
		while (ft_isspace(line[i]))
			i++;
		if (ft_isalnum(line[i]))
			return (false);
		if (!line[i] || line[i] == '<' || line[i] == '&' || line[i] == '|'
			|| line[i] == '>')
			return (true);
	}
	return (!is_token_valid(line, "<", in_eof));
}

bool	did_great_sentinel_see(char *line, bool in_eof)
{
	int	i;

	i = 1;
	if (!line[0] || line[0] != '>')
		return (false);
	if (line[1] == '>')
	{
		line++;
		while (ft_isspace(line[i]))
			i++;
		if (ft_isalnum(line[i]))
			return (false);
	}
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] && ft_isalnum(line[i]))
		return (false);
	return (!is_token_valid(line, ">", in_eof));
}

bool	did_other_sentinel_see(char *line, bool in_eof)
{
	if (!line[0] || line[0] != ';')
		return (false);
	return (!is_token_valid(line, ":", in_eof));
}

bool	did_logical_sentinel_see(char *line, bool in_eof)
{
	if (!line[0] || line[0] != '&')
		return (false);
	if (line[1] == '&')
	{
		line++;
		return (!is_token_valid(line, "&&", in_eof));
	}
	return (!is_token_valid(line, "&", in_eof));
}
