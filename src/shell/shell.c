/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:21:29 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/12 23:20:24 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_free(t_input *input)
{
	if (!input)
		return ;
	if (input->redir_code)
		string_array_free(&input->redir_code);
	if (input->redir_input)
		string_array_free(&input->redir_input);
	if (input->line)
	{
		free(input->line);
		input->line = NULL;
	}
	if (input->stack)
	{
		free(input->stack);
		input->stack = NULL;
	}
	ft_memset(input, 0, sizeof(t_input));
}

void	shell_free(t_sh *shell)
{
	if (shell->line)
	{
		free(shell->line);
		shell->line = NULL;
	}
	if (shell->pipe.in)
		close(shell->pipe.in);
	string_array_free(&shell->env);
	string_free(&shell->prompt);
}

void	shell_init(t_sh *shell, char **env)
{
	char	*shlvl_val;
	char	*shlvl_env;

	ft_memset(shell, 0, sizeof(*shell));
	shell->name = "minishell";
	shell->pipe.in = STDIN_FILENO;
	shell->pipe.out = STDOUT_FILENO;
	shell->env = string_array_dup(env);
	shlvl_val = ft_itoa(ft_atoi(env_get(shell, "SHLVL")) + 1);
	if (!shlvl_val)
		shell_exit(shell);
	shlvl_env = ft_strcat("SHLVL=", shlvl_val);
	free(shlvl_val);
	if (!shlvl_env)
		shell_exit(shell);
	env_set(shell, "SHLVL", shlvl_env);
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
