/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:42:39 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/25 17:58:53 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	basic_exec(t_sh *shell, int exec)
{
	if (exec)
		lex_eof(shell);
	if (did_eye_of_sawron(shell))
		return ;
	if (count_redir_in_line(shell, shell->line, 0, 0))
		treat_redirections(&shell->input, shell);
	shell->ast = ast_create(shell, ft_strdup(shell->line));
	exec_ast(shell->ast);
	if (!exec)
		stack_to_history(shell->line, shell);
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
	errno = false;
	shell->is_running = true;
	while (shell->is_running)
	{
		g_signal.is_sigint = false;
		exec = input_read(shell);
		if (!shell->line && !shell->is_interactive)
			shell_exit(shell);
		if (*shell->line == '#')
			continue ;
		if (shell->line)
			basic_exec(shell, exec);
	}
	shell_exit(shell);
}
