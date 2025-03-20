/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:37:31 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/20 10:24:22 by jvoisard         ###   ########.fr       */
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
		return (ENOENT);
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
	char	*path;

	if (string_array_len(node->tokens) > 2)
		return (throw(node, (char *[]){"cd: too many arguments", NULL}));
	path = node->tokens[1];
	if (!path || !ft_strcmp(path, "--"))
	{
		path = env_get(node->shell, "HOME");
		if (!path)
			return (throw(node, (char *[]){"cd: HOME not set", NULL}));
	}
	else if (!ft_strcmp(path, "-"))
	{
		path = env_get(node->shell, "OLDPWD");
		if (!path)
			return (throw(node, (char *[]){"cd: OLDPWD not set", NULL}));
		ft_putstr(path);
		ft_putstr("\n");
	}
	return (change_dir(node, path));
}
