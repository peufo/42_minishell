/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 23:15:32 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/04 21:26:57 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_sh *shell)
{
	char	**env;

	if (!shell->env)
		return (1);
	env = shell->env;
	while (*env)
	{
		ft_putstr_fd(*env, shell->pipe.out);
		ft_putstr_fd("\n", shell->pipe.out);
		env++;
	}
	return (0);
}

char	*get_env(t_sh *shell, char *varname)
{
	char	*key;
	char	len;
	char	**arr_value;
	char	*value;

	len = ft_strlen(varname) + 2;
	key = ft_calloc(len, 1);
	if (!key)
		return (NULL);
	ft_strlcpy(key, varname, len);
	ft_strlcat(key, "=", len);
	arr_value = string_array_find_start_with(shell->env, key);
	free(key);
	if (!arr_value)
		return (NULL);
	value = *arr_value;
	while (*value && *value != '=')
		value++;
	value++;
	return (value);
}
