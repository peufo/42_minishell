/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:37:44 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/11 04:36:37 by dyodlm           ###   ########.fr       */
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

	arg = shell->ast->args[1];
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
