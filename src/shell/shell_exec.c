/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 05:58:39 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/03 20:56:42 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ast_build_and_exec(t_sh *shell)
{
	shell->ast_error = false;
	shell->ast = ast_create(shell, ft_strdup(shell->line));
	if (shell->ast_error)
		throw(shell->ast, (char *[]){"Parsing failed 🤨", NULL});
	else
		exec_ast(shell->ast);
	ast_free(&shell->ast);
}

void	shell_exec(t_sh *shell)
{
	shell->is_interactive = isatty(shell->fd_in);
	shell->is_running = true;
	while (shell->is_running)
	{
		errno = false;
		g_is_sigint = false;
		input_read(shell);
		if (g_is_sigint)
			continue ;
		if (!shell->line)
			break ;
		if (ft_isempty(shell->line) || *shell->line == '#')
			continue ;
		ast_build_and_exec(shell);
	}
	shell_exit(shell);
}
