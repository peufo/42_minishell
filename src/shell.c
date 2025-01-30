/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:21:29 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/30 16:05:17 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shell_free(t_sh *shell)
{
	if (shell->line)
	{
		free(shell->line);
		shell->line = NULL;
	}
	if (!shell->is_interactive && shell->pipe.in != -1)
		close(shell->pipe.in);
	string_array_free(&shell->env);
}

void	shell_init(t_sh *shell, char **env)
{
	ft_memset(shell, 0, sizeof(*shell));
	shell->name = "minishell";
	shell->pipe.in = STDIN_FILENO;
	shell->pipe.out = STDOUT_FILENO;
	shell->env = string_array_dup(env);
	if (!shell->env)
		return (shell_exit(shell));
}

void	shell_exec(t_sh *shell)
{
	shell->is_interactive = isatty(shell->pipe.in);
	errno = false;
	shell->is_running = true;
	while (shell->is_running)
	{
		input_read(shell);
		if (!shell->line || !*shell->line)
			break ;
		debug_arr(shell, (char *[]){"INPUT: ", shell->line, NULL});
		lex(shell);
		parse(shell);
		executor(shell);
	}
	shell_exit(shell);
}

void	shell_exit(t_sh *shell)
{
	shell_free(shell);
	lex_free(shell);
	parse_free(shell);
	debug(shell, "\n[ CLEAN EXIT OK ]\n");
	close(shell->debug_fd);
	if (!errno)
		exit(0);
	perror(shell->name);
	exit(1);
}
