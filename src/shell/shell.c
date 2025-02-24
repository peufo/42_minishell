/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD:src/shell.c
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:21:29 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/24 15:01:25 by jvoisard         ###   ########.fr       */
=======
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:21:29 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/20 08:55:42 by dyodlm           ###   ########.fr       */
>>>>>>> origin/EOF:src/shell/shell.c
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

<<<<<<< HEAD:src/shell.c
void	shell_exec(t_sh *shell)
{
	shell->is_interactive = isatty(shell->pipe.in);
	errno = false;
	shell->is_running = true;
	debug(shell, "INIT SHELL AT : ");
	debug(shell, __TIME__);
	debug(shell, "\n\n");
	while (shell->is_running)
	{
		input_read(shell);
		if (!shell->line)
			break ;
		debug_input(shell);
		lex(shell);
		shell->ast = ast_create(
				shell,
				string_array_dup(shell->lexer.tokens)
				);
		ast_debug(shell->ast, 0);
		exec_ast(shell->ast);
		lex_free(shell);
		ast_free(&shell->ast);
	}
	shell_exit(shell);
}

=======
>>>>>>> origin/EOF:src/shell/shell.c
void	shell_exit(t_sh *shell)
{
	lex_free(shell);
	ast_free(&shell->ast);
	shell_free(shell);
	debug(shell, "\n[ CLEAN EXIT OK ]\n");
	close(shell->debug_fd);
	if (!errno)
		exit(0);
	perror(shell->name);
	exit(1);
}
