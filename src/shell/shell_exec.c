/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:42:39 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/03 09:08:52 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	basic_exec(t_sh *shell, int exec)
{
	debug_input(shell);
	if (exec || ft_strnstr(shell->line, "<<", ft_strlen(shell->line)))
		lex_eof(shell);
	shell->ast = ast_create(shell, ft_strdup(shell->line));
	ast_debug(shell->ast, 0);
	exec_ast(shell->ast);
	input_free(shell->input);
	lex_free(&shell->lexer);
	ast_free(&shell->ast);
}

void	shell_exec(t_sh *shell)
{
	int		exec;

	shell->input = ft_calloc(1, sizeof(t_input));
	shell->input->state = LEXER_DEFAULT;
	shell->is_interactive = isatty(shell->pipe.in);
	errno = false;
	shell->is_running = true;
	debug(shell, "INIT SHELL AT : ");
	debug(shell, __TIME__);
	debug(shell, "\n\n");
	while (shell->is_running)
	{
		exec = input_read(shell);
		if (!shell->line)
			break ;
		basic_exec(shell, exec);
	}
	shell_exit(shell);
}
