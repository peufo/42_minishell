/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:37:44 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/21 20:01:09 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_set(char **env, char *name, char *value)
{
	(void)env;
	free(name);
	(void)value;
}

int	builtin_export(t_sh *shell, t_cmd *cmd)
{
	char	*name;
	char	*value;
	int		i;

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
	env_set(shell->env, name, value);
	return (0);
}
