/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:12:21 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/15 15:01:07 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_paths(t_sh *shell)
{
	char	**path_var;
	char	*cursor_start;
	char	*cursor_end;
	char	**paths;

	paths = NULL;
	path_var = string_array_find_start_with(shell->env, "PATH=");
	if (!path_var)
		return (NULL);
	cursor_start = *path_var + 5;
	cursor_end = cursor_start;
	while (*cursor_end)
	{
		while (*cursor_end && *cursor_end != ':')
			cursor_end++;
		string_array_push(&paths, ft_strcut(cursor_start, cursor_end));
		if (!*cursor_end)
			break ;
		cursor_end++;
		cursor_start = cursor_end;
	}
	return (paths);
}

static char	*build_path(char *dir, char *name)
{
	char	*dir_slash;
	char	*path;

	if (dir[ft_strlen(dir) - 1] == '/')
		dir_slash = ft_strdup(dir);
	else
		dir_slash = ft_strcat(dir, "/");
	if (!dir_slash)
		return (NULL);
	path = ft_strcat(dir_slash, name);
	free(dir_slash);
	return (path);
}

static char	*find_bin(char *dir, char *name)
{
	DIR				*dirp;
	struct dirent	*dp;

	dirp = opendir(dir);
	if (!dirp)
	{
		errno = false;
		return (NULL);
	}
	while (true)
	{
		dp = readdir(dirp);
		if (!dp)
			break ;
		if (!ft_strcmp(dp->d_name, name))
		{
			closedir(dirp);
			return (build_path(dir, name));
		}
	}
	closedir(dirp);
	return (NULL);
}

int	exec_bin(t_ast *node)
{
	char	**paths;
	char	**dir;
	char	*bin;

	if (**node->tokens == '.' || **node->tokens == '/')
	{
		if (execve(*node->tokens, node->tokens, node->shell->env) == -1)
			shell_exit(node->shell);
		return (0);
	}
	paths = get_paths(node->shell);
	dir = paths;
	bin = NULL;
	while (*dir && !bin)
	{
		bin = find_bin(*dir, *node->tokens);
		dir++;
	}
	string_array_free(&paths);
	if (!bin)
		return (throw(node, (char *[]){"Command not found", NULL}));
	signal(SIGQUIT, SIG_DFL);
	if (execve(bin, node->tokens, node->shell->env) == -1)
		shell_exit(node->shell);
	return (0);
}
