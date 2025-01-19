/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:14:44 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/19 23:17:03 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bfunc	get_builtin(t_command *cmd)
{
	int					i;
	static t_builtin	builtins[] = {
	{"echo", builtin_echo},
	{"cd", builtin_echo},
	{"pwd", builtin_echo},
	{"export", builtin_echo},
	{"unset", builtin_echo},
	{"env", builtin_env},
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
