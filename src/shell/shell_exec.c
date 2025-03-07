/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:42:39 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/08 14:05:18 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t	g_signal_received = 0;

void	handle_signal(int sig)
{
	g_signal_received = sig;
}

static void	ready_to_go(t_sh *shell)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		shell_exit(shell);
	node = ast_create(shell, "echo bye bye");
	ast_parse(node);
	exec_ast(node);
	shell_exit(shell);
}

static void	basic_exec(t_sh *shell, int exec)
{
	debug_input(shell);
	if (exec)
		lex_eof(shell);
	treat_redirections(shell->input, shell);
	printf("Out of input\n");
	shell->ast = ast_create(shell, ft_strdup(shell->line));
	ast_debug(shell->ast, 0);
	exec_ast(shell->ast);
	if (!exec)
		stack_to_history(shell->line, shell);
	input_free(shell->input);
	ast_free(&shell->ast);
}

void	shell_exec(t_sh *shell)
{
	int					exec;

	shell->input = ft_calloc(1, sizeof(t_input));
	shell->input->state = LEXER_DEFAULT;
	shell->is_interactive = isatty(shell->pipe.in);
	errno = false;
	shell->is_running = true;
	DEBUG("INIT SHELL AT : %s\n\n", __TIME__);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	while (shell->is_running)
	{
		if (g_signal_received == SIGINT || g_signal_received == SIGQUIT)
			break ;
		exec = input_read(shell, g_signal_received);
		if (!shell->line)
			break ;
		if (*shell->line == '#')
			continue ;
		basic_exec(shell, exec);
	}
	ready_to_go(shell);
}
