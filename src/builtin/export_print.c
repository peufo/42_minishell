/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:50:03 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/15 14:33:40 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_cmp(char *a, char *b)
{
	while (*a && *b && *a == *b && *a != '=' && *b != '=')
	{
		a++;
		b++;
	}
	if (*a == *b)
		return (0);
	if (*a == '=')
		return (1);
	if (*b == '=')
		return (0);
	return (*a < *b);
}

static void	print_env(char *env)
{
	if (env[0] == '_' && env[1] == '=')
		return ;
	ft_putstr("declare -x ");
	while (*env && *env != '=')
		write(STDOUT_FILENO, env++, 1);
	if (!*env)
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	write(STDOUT_FILENO, env++, 1);
	write(STDOUT_FILENO, "\"", 1);
	while (*env)
		write(STDOUT_FILENO, env++, 1);
	write(STDOUT_FILENO, "\"\n", 2);
}

int	builtin_export_print(t_ast *node)
{
	int		*indexes;
	int		i;

	indexes = string_array_create_indexes(node->shell->env, env_cmp);
	if (!indexes)
		return (shell_exit(node->shell), 1);
	i = 0;
	while (node->shell->env[i])
	{
		print_env(node->shell->env[indexes[i]]);
		i++;
	}
	free(indexes);
	return (0);
}
