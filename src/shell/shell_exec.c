/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:42:39 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/28 09:45:45 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	basic_exec(t_sh *shell)
{
	if (count_redir_in_line(shell, shell->line, 0, 0))
		treat_redirections(&shell->input, shell);
	shell->ast = ast_create(shell, ft_strdup(shell->line));
	exec_ast(shell->ast);
	input_free(&shell->input);
	ast_free(&shell->ast);
}

void	shell_exec(t_sh *shell)
{
	int					exec;

	printf("New exec\n");
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
		if ((exec == -1 || (exec == 1 && !lex_eof(shell)) || did_eye_of_sawron(shell, 0)))
			return (shell_exec(shell));
		if (!shell->line && !shell->is_interactive)
			shell_exit(shell);
		if (*shell->line == '#')
			continue ;
		if (shell->line)
			basic_exec(shell);
	}
	shell_exit(shell);
}
