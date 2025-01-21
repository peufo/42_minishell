/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 23:15:32 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/21 19:26:50 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_count(char **env)
{
	int	index;

	index = 0;
	while (env[index])
		index++;
	return (index + 1);
}

void	env_free(char **env)
{
	char	**cursor;

	if (!env)
		return ;
	cursor = env;
	while (*cursor)
		free(*(cursor++));
	free(env);
}

void	env_init(t_sh *shell, char **env)
{
	int	i;

	shell->env = ft_calloc(env_count(env) + 1, sizeof(*env));
	if (!shell->env)
		return (shell_exit(shell));
	i = 0;
	while (env[i])
	{
		shell->env[i] = ft_strdup(env[i]);
		if (!shell->env[i])
			return (shell_exit(shell));
		i++;
	}
}

int	builtin_env(t_sh *shell, t_cmd *cmd)
{
	char	**env;

	(void)cmd;
	if (!shell->env)
		return (1);
	env = shell->env;
	while (*env)
	{
		ft_putstr_fd(*env, shell->pipe.out);
		ft_putstr_fd("\n", shell->pipe.out);
		env++;
	}
	return (0);
}
