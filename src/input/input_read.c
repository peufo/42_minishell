/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:36:57 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/14 18:05:02 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

void	input_read(t_sh	*shell)
{
	if (shell->line.content)
		free(shell->line.content);
	if (shell->is_interactive)
		shell->line.content = readline("minishell>");
	else
		shell->line.content = get_next_line(shell->pipe.in);
	if (errno)
		shell_exit(shell);
	if (!shell->line.content)
	{
		shell->is_running = false;
		return ;
	}
	shell->line.no++;
}
