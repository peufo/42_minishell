/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:37:31 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/07 09:55:32 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_parent(t_string *cwd)
{
	char	*cursor;

	cursor = cwd->value;
	if (!*cursor)
		return ;
	while (*cursor)
		cursor++;
	cursor--;
	while (cursor > cwd->value && *cursor != '/')
		*(cursor--) = '\0';
	if (*cursor == '/')
		*cursor = '\0';
	return ;
}

static char	*get_child(t_string *cwd, char *path)
{
	char	*cursor;

	string_push_char(cwd, '/');
	cursor = path;
	while (*cursor && *cursor != '/')
		cursor++;
	if (!*cursor)
	{
		string_push_str(cwd, path);
		return (cursor);
	}
	*cursor = '\0';
	string_push_str(cwd, path);
	return (cursor + 1);
}

static void	resolve_path(t_sh *shell, t_string *cwd, char *path)
{
	while (*path && *path == '/')
		path++;
	if (!*path)
		return ;
	if (ft_startwith(path, ".."))
	{
		get_parent(cwd);
		return (resolve_path(shell, cwd, path + 2));
	}
	if (ft_startwith(path, "."))
		return (resolve_path(shell, cwd, path + 1));
	path = get_child(cwd, path);
	return (resolve_path(shell, cwd, path));
}

// TODO
bool	directory_exist(char *path)
{
	(void)path;
	return (true);
}

int	builtin_cd(t_sh *shell)
{
	char		*path;
	t_string	cwd;

	ft_bzero(&cwd, sizeof(cwd));
	if (!shell->ast->args[1])
		path = ft_strdup(env_get(shell, "HOME"));
	else
		path = ft_strdup(shell->ast->args[1]);
	if (!ft_startwith(path, "/"))
		string_push_str(&cwd, shell->cwd);
	resolve_path(shell, &cwd, path);
	free(path);
	if (!directory_exist(cwd.value))
	{
		free(cwd.value);
		return (1);
	}
	free(shell->cwd);
	shell->cwd = cwd.value;
	return (0);
}
