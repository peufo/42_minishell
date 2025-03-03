/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:21:29 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/03 07:14:35 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_free(t_input *input)
{
	if (!input)
		return ;
	ft_memset(input, 0, sizeof(t_input));
	if (input->redir_code)
	{
		free(input->redir_code);
		input->redir_code = NULL;
	}
	if (input->redir_input)
	{
		free(input->redir_input);
		input->redir_input = NULL;
	}
	ft_memset(input, 0, sizeof(t_input));
}

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

void	shell_exit(t_sh *shell)
{
	input_free(shell->input);
	lex_free(&shell->lexer);
	ast_free(&shell->ast);
	shell_free(shell);
	debug(shell, "\n[ CLEAN EXIT OK ]\n");
	close(shell->debug_fd);
	if (!errno)
		exit(0);
	perror(shell->name);
	exit(1);
}
