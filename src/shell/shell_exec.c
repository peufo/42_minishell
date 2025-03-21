/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:42:39 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/19 10:04:44 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	basic_exec(t_sh *shell, int exec)
{
	if (exec)
		lex_eof(shell);
	if (did_eye_of_sawron(shell))
		return ;
	treat_redirections(&shell->input, shell);
	shell->ast = ast_create(shell, ft_strdup(shell->line));
	ast_debug(shell->ast, 0);
	exec_ast(shell->ast);
	if (!exec)
		stack_to_history(shell->line, shell);
	input_free(&shell->input);
	ast_free(&shell->ast);
}

void	shell_exec(t_sh *shell)
{
	int					exec;

	ft_bzero(&shell->input, sizeof(t_input));
	shell->input.state = LEXER_DEFAULT;
	shell->is_interactive = isatty(shell->pipe.in);
	errno = false;
	shell->is_running = true;
	DEBUG("INIT SHELL AT : %s\n\n", __TIME__);
	while (shell->is_running)
	{
		actualise(shell);
		if (shell->signal != SIGINT)
		{
			exec = input_read(shell);
			if (!shell->line && !shell->is_interactive)
				shell_exit(shell);
			if (*shell->line == '#')
				continue ;
			if (shell->line)
				basic_exec(shell, exec);
		}
	}
	shell_exit(shell);
}
