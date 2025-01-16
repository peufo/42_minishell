/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:36:57 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/16 01:07:28 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

void	input_read(t_sh	*shell)
{
	if (shell->line)
		free(shell->line);
	if (shell->is_interactive)
		shell->line = readline("minishell>");
	else
		shell->line = get_next_line(shell->pipe.in);
	if (errno)
		shell_exit(shell);
	if (!shell->line)
	{
		shell->is_running = false;
		return ;
	}
	add_history(shell->line);
}
