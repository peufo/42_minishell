/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 05:58:39 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/03 17:09:51 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	basic_exec(t_sh *shell, int exec)
{
	if ((exec == 1 && !lex_eof(shell)))
		return (shell_exec(shell));
	if (did_eye_of_sawron(shell, 0) && !shell->line2)
		return (shell_exec(shell));
	if (count_redir_in_line(shell, shell->line, 0, 0))
		while (!treat_redirections(&shell->input, shell) && !g_is_sigint)
			continue ;
	shell->ast_error = false;
	shell->ast = ast_create(shell, ft_strdup(shell->line));
	if (shell->ast_error && !g_is_sigint)
		throw(shell->ast, (char *[]){"AST parsing error", NULL});
	else
		exec_ast(shell->ast);
	input_free(&shell->input);
	ast_free(&shell->ast);
}

void	shell_exec(t_sh *shell)
{
	int					exec;

	if (shell->input.redir_code || shell->input.redir_input
		|| shell->input.redir_line)
		input_free(&shell->input);
	ft_bzero(&shell->input, sizeof(t_input));
	shell->input.state = LEXER_DEFAULT;
	shell->is_interactive = isatty(shell->pipe.in);
	shell->is_running = true;
	while (shell->is_running)
	{
		errno = false;
		g_is_sigint = false;
		exec = input_read(shell);
		if (!shell->line)
			shell_exit(shell);
		if (*shell->line == '#')
			continue ;
		if (shell->line)
			basic_exec(shell, exec);
	}
	shell_exit(shell);
}
