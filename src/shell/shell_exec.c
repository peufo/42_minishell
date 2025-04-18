/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 05:58:39 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/18 11:46:10 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ast_build_and_exec(t_sh *shell)
{
	if (!ast_is_syntax_ok(shell->line))
	{
		shell->exit_status = 2;
		ft_putstr_fd(shell->name, STDERR_FILENO);
		ft_putstr_fd(": Syntax error\n", STDERR_FILENO);
		return ;
	}
	shell->ast_error = false;
	shell->ast = ast_create(shell, ft_strdup(shell->line));
	if (shell->ast_error)
	{
		throw(shell->ast, (char *[]){"Parsing failed 🤨", NULL});
		ast_free(&shell->ast);
		return ;
	}
	exec_ast(shell->ast);
	if (shell->exit_status == 131)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
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
			shell->exit_status = 130;
		if (!shell->line)
			break ;
		if (ft_isempty(shell->line) || *shell->line == '#')
			continue ;
		ast_build_and_exec(shell);
	}
	shell_exit(shell);
}
