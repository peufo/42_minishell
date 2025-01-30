/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:14:44 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/30 12:39:52 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bfunc	get_builtin(t_cmd *cmd)
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
		if (!ft_strcmp(cmd->arg.data.text, builtins[i].name))
			return (builtins[i].function);
		i++;
	}
	return (NULL);
}
