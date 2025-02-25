/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:37:44 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/24 15:26:14 by jvoisard         ###   ########.fr       */
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

int	builtin_export(t_ast *node)
{
	char	*value;
	char	*arg;
	int		equal_index;

	arg = node->tokens[1];
	if (!arg)
		return (0);
	equal_index = find_index(arg, '=');
	if (equal_index == -1 || !arg[equal_index + 1])
		return (1);
	value = ft_strdup(arg);
	if (!value)
		return (1);
	arg[equal_index] = '\0';
	env_set(node->shell, arg, value);
	return (0);
}
