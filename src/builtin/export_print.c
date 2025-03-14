/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:50:03 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/12 23:20:39 by jvoisard         ###   ########.fr       */
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

static int	get_index(t_ast *node, char *env_val)
{
	int		index;
	char	**env;

	index = 0;
	env = node->shell->env;
	while (*env)
		index += env_cmp(*(env++), env_val);
	return (index);
}

static int	*create_indexes(t_ast *node)
{
	int		env_count;
	int		*indexes;
	int		i;

	env_count = string_array_len(node->shell->env);
	indexes = ft_calloc(env_count, sizeof(*indexes));
	if (!indexes)
		return (NULL);
	i = 0;
	while (node->shell->env[i])
	{
		indexes[get_index(node, node->shell->env[i])] = i;
		i++;
	}
	return (indexes);
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

	indexes = create_indexes(node);
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
