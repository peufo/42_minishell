/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:36:57 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/19 11:08:30 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

static bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
		if (!ft_isspace(line[i++]))
			return (0);
	return (1);
}

void	input_read(t_sh	*shell)
{
	if (shell->line)
		free(shell->line);
	if (shell->is_interactive)
	{
		shell->line = readline("MyMinishell>");
		if (!shell->line)
			shell_exit(shell);
		errno = false;
		add_history(shell->line);
	}
	else
		shell->line = get_next_line(shell->pipe.in);
	if (errno)
		shell_exit(shell);
	if (shell->line && is_empty_line(shell->line))
		input_read(shell);
}
