/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:21:29 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/03 19:00:45 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_free(t_sh *shell)
{
	if (shell->line)
	{
		free(shell->line);
		shell->line = NULL;
	}
	if (shell->fd_in)
		close(shell->fd_in);
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
	ft_bzero(shell, sizeof(*shell));
	shell->name = "minishell";
	shell->fd_in = STDIN_FILENO;
	shell->env = string_array_dup(env);
	shell_init_env(shell);
	if (!shell->env)
		return (shell_exit(shell));
}

void	shell_exit(t_sh *shell)
{
	ast_free(&shell->ast);
	shell_free(shell);
	if (errno)
		perror(shell->name);
	if (errno && !shell->exit_status)
		exit(errno);
	exit(shell->exit_status);
}
