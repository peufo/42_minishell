/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:37:44 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/22 15:17:00 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO
static void	env_set(t_sh *shell, char *name, char *value)
{
	(void)shell;
	free(name);
	(void)value;
}

int	builtin_export(t_sh *shell)
{
	char	*name;
	char	*value;
	int		i;
	t_cmd	*cmd;

	cmd = &shell->exec.cmd;
	if (!cmd->args->next->content)
		return (0);
	name = ft_strdup(cmd->args->next->content);
	value = NULL;
	if (!name)
		return (0);
	i = 0;
	while (name[i])
	{
		if (name[i] == '=')
		{
			name[i] = '\0';
			value = name + i + 1;
		}
		i++;
	}
	env_set(shell, name, value);
	return (0);
}
