/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:08:40 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/26 08:11:18 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_display(t_sh *shell, char *error)
{
	throw_shell(shell, (char *[]){"Your syntax is shit. What's with <<",
		error, ">> ?", NULL});
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

static char	*look_for_problems(char *cursor)
{
	t_sent			handler;
	t_errors		i;
	static char		*message[] = {
		"|", "&", "<", ">", ";", NULL
	};

	i = 0;
	while (i < 6)
	{
		handler = get_sentinel(i++);
		if (handler && handler(cursor))
			return (message[i]);
	}
	return (NULL);
}

bool	did_eye_of_sawron(t_sh *shell)
{
	bool	quotes[2];
	char	*cursor;
	char	*head;
	char	*problem;

	problem = NULL;
	ft_bzero(&quotes, sizeof(quotes));
	init_error_checker(&cursor, &head, shell);
	if (!check_start(shell, cursor))
		return (free(head), true);
	while (*cursor)
	{
		check_quotes(*cursor, &quotes[0], &quotes[1]);
		if (!quotes[0] && !quotes[1])
			problem = look_for_problems(cursor);
		if (problem)
			return (free(head), error_display(shell, problem), true);
		cursor++;
	}
	return (free(head), false);
}
