/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:08:40 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/27 11:00:38 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_token_valid(char *line, char *token, bool in_eof)
{
	short int	i;
	bool		ignore_end_op;

	i = 1;
	ignore_end_op = is_eof_token(token, in_eof);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if ((!line[i] || (i == 1 && ft_isalpha(line[i]))) && ignore_end_op)
		return (true);
	if (line[i] == '<' || line[i] == '>' || line[i] == '&' || line[i] == '|')
		return (false);
	return (true);
}

bool	check_start(t_sh *shell, char *s)
{
	if (*s == '&')
	{
		if (s[1] == '&')
			return (error_display(shell, "&&"), false);
		return (error_display(shell, "&"), false);
	}
	if (*s == '|')
	{
		if (s[1])
			return (error_display(shell, "||"), false);
		return (error_display(shell, "|"), false);
	}
	if (*s == ';')
		return (error_display(shell, ";"), false);
	if ((*s == '<' && s[1] == '|') || (*s == '>' && s[1] == '|'))
		return (error_display(shell, "|"), false);
	return (true);
}

static t_sent	get_sentinel(t_errors i)
{
	static t_sent	sentinels[] = {
		did_pipe_sentinel_see,
		did_logical_sentinel_see,
		did_less_sentinel_see,
		did_great_sentinel_see,
		did_other_sentinel_see,
		NULL
	};

	return (sentinels[i]);
}

static char	*look_for_problems(char *cursor, bool in_eof)
{
	t_sent			handler;
	t_errors		i;
	static char		*message[] = {
		"|", "&", "newline", ">", ";", NULL
	};

	i = 0;
	while (i++ < 6)
	{
		handler = get_sentinel(i - 1);
		if (handler && handler(cursor, in_eof))
			return (message[i - 1]);
	}
	return (NULL);
}

bool	did_eye_of_sawron(t_sh *shell, bool in_eof)
{
	bool	quotes[2];
	char	*cursor;
	char	*head;
	char	*problem;

	problem = NULL;
	quotes[0] = false;
	quotes[1] = false;
	init_error_checker(&cursor, &head, shell);
	if (!cursor)
		return (free(head), true);
	if (!check_start(shell, cursor))
		return (free(head), true);
	while (*cursor && cursor[1])
	{
		check_quotes(*cursor, &quotes[0], &quotes[1]);
		if (!quotes[0] && !quotes[1])
			problem = look_for_problems(cursor, in_eof);
		if (problem)
			return (free(head), error_display(shell, problem), true);
		cursor++;
	}
	return (free(head), false);
}
