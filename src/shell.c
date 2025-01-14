/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:21:29 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/14 18:05:12 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_exit(t_sh *shell)
{
	if (shell->line.content)
	{
		free(shell->line.content);
		shell->line.content = NULL;
	}
	if (!shell->is_interactive && shell->pipe.in != -1)
		close(shell->pipe.in);
	if (!errno)
		exit(0);
	perror(shell->name);
	exit(1);
}

void	shell_exec(t_sh *shell)
{
	if (!shell->pipe.in)
		shell->pipe.in = STDIN_FILENO;
	if (!shell->pipe.out)
		shell->pipe.out = STDOUT_FILENO;
	shell->is_interactive = isatty(shell->pipe.in);
	errno = false;
	shell->is_running = true;
	shell->line.no = 0;
	while (shell->is_running)
	{
		input_read(shell);
		ft_putstr_fd("TODO parse: ", shell->pipe.out);
		ft_putstr_fd(shell->line.content, shell->pipe.out);
		ft_putstr_fd("\n", shell->pipe.out);
	}	
}
