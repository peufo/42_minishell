/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:37:31 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/17 17:50:01 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(t_sh *shell)
{
	char	*path;
	char	*cwd;
	int		status;

	if (!shell->ast->args[1])
		path = ft_strdup(env_get(shell, "HOME"));
	else
		path = ft_strdup(shell->ast->args[1]);
	if (!path)
		return (1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	status = chdir(path);
	free(path);
	env_set(shell, "OLDPWD", ft_strcat("OLDPWD=", cwd));
	free(cwd);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	env_set(shell, "PWD", ft_strcat("PWD=", cwd));
	free(cwd);
	return (status);
}
