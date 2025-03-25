/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:08:40 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/25 17:59:57 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	help(t_sh *shell, char *error)
{
	throw_shell(shell, (char *[]){"Your syntax is shit. What's with <<",
		error, ">> ?", NULL});
}

static int	pipe_sentinel(char *line)
{
	int	i;

	i = 1;
	if (!line[0] || line[0] != '|')
		return (0);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if ((line[i] && ft_isalnum(line[i])) || line[1] == '|' || line[i] == '('
		|| line[i] == '<' || line[i] == '>' || line[i] == '\\')
		return (0);
	return (1);
}

static int	redir_sentinel(char *line)
{
	int	i;

	i = 1;
	if (!line[0] || line[0] != '<' || line[0] != '>' || line[i] == '\\')
		return (0);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] && ft_isalnum(line[i]))
		return (0);
	return (1);
}

bool	check_start(t_sh *shell, char *cursor)
{
	if (*cursor == '&')
	{
		if (cursor[1] == '&')
			return (help(shell, "&&"), false);
		return (help(shell, "&"), false);
	}
	if (*cursor == '|')
	{
		if (cursor[1])
			return (help(shell, "||"), false);
		return (help(shell, "|"), false);
	}
	if (*cursor == ';')
		return (help(shell, ";"), false);
	return (true);
}

bool	did_eye_of_sawron(t_sh *shell)
{
	bool	quotes[2];
	char	*cursor;
	char	*head;

	if (!shell->line)
		return (true);
	ft_bzero(&quotes, sizeof(quotes));
	init_error_checker(&cursor, &head, shell);
	if (!check_start(shell, cursor))
		return (free(head), false);
	while (*cursor)
	{
		check_quotes(*cursor, &quotes[0], &quotes[1]);
		if (!quotes[0] && !quotes[1])
		{
			if (pipe_sentinel(cursor))
				return (free(head), help(shell, "|"), true);
			if (redir_sentinel(cursor))
				return (free(head), help(shell, "><"), true);
		}
		cursor++;
	}
	return (free(head), false);
}
