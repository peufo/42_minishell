/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:37:31 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/23 15:04:18 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(t_ast *node)
{
	char	*path;
	char	*cwd;
	int		status;

	if (!node->tokens[1])
		path = ft_strdup(env_get(node->shell, "HOME"));
	else
		path = ft_strdup(node->tokens[1]);
	if (!path)
		return (1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	status = chdir(path);
	free(path);
	env_set(node->shell, "OLDPWD", ft_strcat("OLDPWD=", cwd));
	free(cwd);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	env_set(node->shell, "PWD", ft_strcat("PWD=", cwd));
	free(cwd);
	return (status);
}
