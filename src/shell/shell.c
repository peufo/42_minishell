/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:21:29 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/19 18:31:54 by jvoisard         ###   ########.fr       */
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

static void	shell_init_env(t_sh *shell)
{
	char	*env_val;
	char	*env_row;

	env_val = ft_itoa(ft_atoi(env_get(shell, "SHLVL")) + 1);
	if (!env_val)
		shell_exit(shell);
	env_row = ft_strcat("SHLVL=", env_val);
	free(env_val);
	if (!env_row)
		shell_exit(shell);
	env_set(shell, "SHLVL", env_row);
	env_val = getcwd(NULL, 0);
	if (!env_val)
		shell_exit(shell);
	env_row = ft_strcat("PWD=", env_val);
	free(env_val);
	if (!env_row)
		shell_exit(shell);
	env_set(shell, "PWD", env_row);
	if (!env_get(shell, "OLDPWD"))
		env_set(shell, "OLDPWD", ft_strdup("OLDPWD"));
}

void	shell_init(t_sh *shell, char **env)
{
	ft_memset(shell, 0, sizeof(*shell));
	shell->name = "minishell";
	shell->pipe.in = STDIN_FILENO;
	shell->pipe.out = STDOUT_FILENO;
	shell->env = string_array_dup(env);
	shell_init_env(shell);
	if (!shell->env)
		return (shell_exit(shell));
}

void	shell_exit(t_sh *shell)
{
	input_free(&shell->input);
	ast_free(&shell->ast);
	shell_free(shell);
	DEBUG("\n[%d]\t🏁🏁🏁 CLEAN EXIT OK 🏁🏁🏁\n", getpid());
	DEBUG_CLOSE();
	if (errno)
		perror(shell->name);
	if (errno && !shell->exit_status)
		exit(errno);
	exit(shell->exit_status);
}
