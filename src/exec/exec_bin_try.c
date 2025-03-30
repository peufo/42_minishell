/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin_try.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 11:47:48 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/30 12:03:50 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_directory(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

bool	is_env_path_defined(t_ast	*node)
{
	char	*env_path;

	env_path = env_get(node->shell, "PATH");
	return (!!env_path && !!*env_path);
}

static int	catch_err(t_ast *node, char *path, char *msg, int status)
{
	node->status = status;
	if (path)
		throw(node, (char *[]){path, msg, NULL});
	else
		throw(node, (char *[]){msg, NULL});
	return (status);
}

int	exec_bin_try(t_ast *node, char *path)
{
	static char	is_dir[] = ": Is a directory";
	static char	is_no_ent[] = ": No such file or directory";
	static char	is_no_acces[] = ": Permission denied";
	static char	is_bad_arg[]
		= ".: filename argument required\n.: usage: . filename [arguments]";

	if (ft_strcmp(path, ".") == 0)
		return (catch_err(node, NULL, is_bad_arg, 2));
	if (is_directory(path))
		return (catch_err(node, path, is_dir, 126));
	if (access(path, X_OK) == -1)
	{
		exec_redir_restore_std(node);
		if (errno == ENOENT)
			return (catch_err(node, path, is_no_ent, 127));
		if (errno == EACCES)
			return (catch_err(node, path, is_no_acces, 126));
	}
	if (execve(path, node->tokens, node->shell->env) == -1)
		shell_exit(node->shell);
	return (0);
}
