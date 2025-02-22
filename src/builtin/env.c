/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 23:15:32 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/22 22:21:20 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_ast *node)
{
	char	**env;

	if (!node->shell->env)
		return (1);
	env = node->shell->env;
	while (*env)
	{
		ft_putstr(*env);
		ft_putstr("\n");
		env++;
	}
	return (0);
}

static char	**get_env_ptr(t_sh *shell, char *varname)
{
	char	*key;
	char	len;
	char	**arr_ptr;

	len = ft_strlen(varname) + 2;
	key = ft_calloc(len, 1);
	if (!key)
		return (NULL);
	ft_strlcpy(key, varname, len);
	ft_strlcat(key, "=", len);
	arr_ptr = string_array_find_start_with(shell->env, key);
	free(key);
	return (arr_ptr);
}

char	*env_get(t_sh *shell, char *varname)
{
	char	**arr_ptr;
	char	*value;

	arr_ptr = get_env_ptr(shell, varname);
	if (!arr_ptr)
		return (NULL);
	value = *arr_ptr;
	while (*value && *value != '=')
		value++;
	value++;
	return (value);
}

void	env_set(t_sh *shell, char *varname, char *env_row)
{
	char	**env_ptr;

	env_ptr = get_env_ptr(shell, varname);
	if (env_ptr)
	{
		free(*env_ptr);
		*env_ptr = env_row;
		return ;
	}
	string_array_push(&shell->env, env_row);
}

void	env_unset(t_sh *shell, char *varname)
{
	char	**arr_ptr;

	arr_ptr = get_env_ptr(shell, varname);
	if (!arr_ptr)
		return ;
	string_array_delete(shell->env, *arr_ptr);
}
