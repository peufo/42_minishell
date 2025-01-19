/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:08:17 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/19 19:07:45 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_builtin_function	get_builtin(t_command *cmd)
{
	int					i;
	static t_builtin	builtins[] = {
	{"echo", builtin_exit},
	{"cd", builtin_exit},
	{"pwd", builtin_exit},
	{"export", builtin_exit},
	{"unset", builtin_exit},
	{"env", builtin_exit},
	{"exit", builtin_exit},
	{NULL, NULL}
	};

	i = 0;
	while (builtins[i].name)
	{
		if (!ft_strcmp(cmd->executable, builtins[i].name))
			return (builtins[i].function);
		i++;
	}
	return (NULL);
}

int	executor(t_sh *shell, t_command *cmd)
{
	t_builtin_function	builtin;

	builtin = get_builtin(cmd);
	if (builtin)
		builtin(shell, cmd);
	printf("TODO: exec command (%s)\n", cmd->executable);
	return (0);
}
