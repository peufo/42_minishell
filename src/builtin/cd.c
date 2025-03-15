/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:37:31 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/15 12:03:43 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_chdir_error(t_ast *node, char *new_path, char *cwd)
{
	char	*error_name;

	free(cwd);
	if (errno == ENOENT)
	{
		throw(node, (char *[]){
			"cd: ",
			new_path,
			": No such file or directory",
			NULL});
		errno = false;
		return (1);
	}
	error_name = ft_strcat(node->shell->name, ": cd: ");
	if (!error_name)
		return (shell_exit(node->shell), 1);
	perror(error_name);
	free(error_name);
	errno = false;
	return (1);
}

static int	change_dir(t_ast *node, char *new_path)
{
	char	*cwd;
	int		status;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	status = chdir(new_path);
	if (errno)
		return (handle_chdir_error(node, new_path, cwd));
	env_set(node->shell, "OLDPWD", ft_strcat("OLDPWD=", cwd));
	free(cwd);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	env_set(node->shell, "PWD", ft_strcat("PWD=", cwd));
	free(cwd);
	return (status);
}

int	builtin_cd(t_ast *node)
{
	char	*home;

	if (string_array_len(node->tokens) > 2)
		return (throw(node, (char *[]){"cd: too many arguments", NULL}));
	if (node->tokens[1])
		return (change_dir(node, node->tokens[1]));
	home = env_get(node->shell, "HOME");
	if (!home)
		return (throw(node, (char *[]){"cd: HOME not set", NULL}));
	return (change_dir(node, home));
}
