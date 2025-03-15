/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:36:57 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/15 15:23:29 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

static bool	lex_check_start(char *line, t_input *input)
{
	if (!line)
		return (BASIC_MOD);
	if (check_string(line) || get_last_token_type(line, input))
		return (BONUS_MOD);
	return (BASIC_MOD);
}

static bool	iss_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
		if (!ft_isspace(line[i++]))
			return (0);
	return (1);
}

bool	input_read(t_sh	*shell)
{
	shell_update_prompt(shell);
	if (shell->line)
	{
		free(shell->line);
		shell->line = NULL;
	}
	if (shell->is_interactive)
	{
		shell->line = readline(shell->prompt.value);
		errno = false;
		if (!lex_check_start(shell->line, &shell->input))
		{
			if (!iss_empty_line(shell->line))
				add_history(shell->line);
		}
	}
	else
		shell->line = get_next_line(shell->pipe.in);
	if (errno)
		shell_exit(shell);
	if (shell->line && iss_empty_line(shell->line))
		input_read(shell);
	return (lex_check_start(shell->line, &shell->input));
}
