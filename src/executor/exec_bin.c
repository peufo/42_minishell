/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:22:31 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/16 23:01:16 by jvoisard         ###   ########.fr       */
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
			break;
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
			return (NULL);
	while (true)
	{
		dp = readdir(dirp);
		if (!dp)
			return (NULL);
		if (!ft_strcmp(dp->d_name, name))
		{
			closedir(dirp);
			return (build_path(dir, name));
		}
	}
	closedir(dirp);
	return (NULL);
}

int	exec_bin(t_sh *shell)
{
	char	**paths;
	char	**dir;
	char	*bin;
	int		ret;

	paths = get_paths(shell);
	dir = paths;
	bin = NULL;
	while (*dir && !bin)
	{
		bin = find_bin(*dir, *shell->ast->args);
		dir++;
	}
	string_array_free(&paths);
	if (!bin)
	{
		throw_error("Command not found", __FILE__, __LINE__);
		return (1);
	}
	ret = execve(bin, shell->ast->args, shell->env);
	free(bin);
	return (ret);
}
