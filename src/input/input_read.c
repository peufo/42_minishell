/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:36:57 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/30 14:50:02 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

void	input_read(t_sh	*shell)
{
	if (shell->line)
		free(shell->line);
	if (shell->is_interactive)
	{
		shell->line = readline("MyMinishell>");
		if (!shell->line)
			shell_exit(shell);
		errno = 0;
		add_history(shell->line);
	}
	else
		shell->line = get_next_line(shell->pipe.in);
	if (errno)
		shell_exit(shell);
}
