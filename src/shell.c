/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:21:29 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/05 01:31:23 by jvoisard         ###   ########.fr       */
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
	free(shell->cwd);
	string_array_free(&shell->env);
}

void	shell_init(t_sh *shell, char **env)
{
	ft_memset(shell, 0, sizeof(*shell));
	shell->name = "minishell";
	shell->pipe.in = STDIN_FILENO;
	shell->pipe.out = STDOUT_FILENO;
	shell->cwd = getcwd(NULL, 0);
	shell->env = string_array_dup(env);
	if (!shell->env || !shell->cwd)
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
		debug_input(shell);
		lex(shell);
		debug_tokens(shell);
		parse(shell);
		debug_ast(shell);
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
