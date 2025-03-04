/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:42:39 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/04 14:09:06 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	basic_exec(t_sh *shell, int exec)
{
	DEBUG("============\nINPUT: %s\n", shell->line);
	if (exec || ft_strnstr(shell->line, "<<", ft_strlen(shell->line)))
		lex_eof(shell);
	shell->ast = ast_create(shell, ft_strdup(shell->line));
	ast_debug(shell->ast, 0);
	exec_ast(shell->ast);
	input_free(shell->input);
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
	DEBUG("INIT SHELL AT : %s\n\n", __TIME__);
	while (shell->is_running)
	{
		exec = input_read(shell);
		if (!shell->line)
			break ;
		if (*shell->line == '#')
			continue ;
		basic_exec(shell, exec);
	}
	shell_exit(shell);
}
