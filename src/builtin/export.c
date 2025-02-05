/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:37:44 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/05 14:56:02 by jvoisard         ###   ########.fr       */
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

int	builtin_export(t_sh *shell)
{
	char	*value;
	char	*arg;
	int		equal_index;

	arg = shell->ast.args[1];
	if (!arg)
		return (0);
	equal_index = find_index(arg, '=');
	if (equal_index == -1 || !arg[equal_index + 1])
		return (1);
	value = ft_strdup(arg);
	if (!value)
		return (1);
	arg[equal_index] = '\0';
	env_set(shell, arg, value);
	return (0);
}
