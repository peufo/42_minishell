/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:21:29 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/05 12:44:48 by jvoisard         ###   ########.fr       */
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
	ast_free(&shell->ast);
	shell_free(shell);
	DEBUG("\n[%d]\t🏁🏁🏁 CLEAN EXIT OK 🏁🏁🏁\n", getpid());
	DEBUG_CLOSE();
	if (!errno)
		exit(0);
	perror(shell->name);
	exit(1);
}
