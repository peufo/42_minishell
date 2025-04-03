/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:13:23 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/03 18:56:47 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exe	get_builtin(char *cmd)
{
	int					i;
	static t_builtin	builtins[] = {
	{"echo", builtin_echo},
	{"cd", builtin_cd},
	{"pwd", builtin_pwd},
	{"export", builtin_export},
	{"unset", builtin_unset},
	{"env", builtin_env},
	{"exit", builtin_exit},
	{NULL, NULL}
	};

	i = 0;
	while (builtins[i].name)
	{
		if (!ft_strcmp(cmd, builtins[i].name))
			return (builtins[i].exe);
		i++;
	}
	return (NULL);
}
