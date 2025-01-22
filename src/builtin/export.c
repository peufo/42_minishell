/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:37:44 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/22 16:57:44 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

static void	env_set(t_sh *shell, char *key, char *value)
{
	char	**existing_value;

	existing_value = string_array_find_start_with(shell->env, key);
	if (existing_value)
	{
		free(*existing_value);
		*existing_value = value;
		return ;
	}
	string_array_push(&shell->env, value);
}

int	builtin_export(t_sh *shell)
{
	char	*value;
	char	*arg;
	int		equal_index;

	arg = (char *)shell->exec.cmd.args->next->content;
	if (!arg)
		return (0);
	equal_index = find_index(arg, '=');
	if (equal_index == -1 || !arg[equal_index + 1])
		return (1);
	value = ft_strdup(arg);
	if (!value)
		return (1);
	arg[equal_index + 1] = '\0';
	env_set(shell, arg, value);
	return (0);
}
