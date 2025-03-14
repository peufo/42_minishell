/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:08:40 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/14 13:07:42 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	help(t_sh *shell, char *error)
{
	throw_error2(shell, (char *[]){"Your syntax is shit. What's with <<",
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
	if (line[i] && ft_isalnum(line[i]))
		return (0);
	return (1);
}

static int	redir_sentinel(char *line)
{
	int	i;

	i = 1;
	if (!line[0] || line[0] != '<' || line[0] != '>')
		return (0);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] && ft_isalnum(line[i]))
		return (0);
	return (1);
}

bool	did_eye_of_sawron(t_sh *shell)
{
	bool	indquote;
	bool	insquote;
	char	*cursor;

	indquote = false;
	insquote = false;
	if (!shell->line)
		return (true);
	cursor = ft_strdup(shell->line);
	while (*cursor)
	{
		check_quotes(*cursor, &indquote, &insquote);
		if (!indquote && !insquote)
		{
			if (pipe_sentinel(cursor))
				return (help(shell, "Pipe"), true);
			if (redir_sentinel(cursor))
				return (help(shell, "Redir"), true);
		}
		cursor++;
	}
	return (false);
}
