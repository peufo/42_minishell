/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:37:31 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/08 12:50:05 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: print error "No such file or directory"
//TODO: don't work with --trace-children=yes ... WHY ?
static int	change_the_directory(char *newpath, t_ast *node)
{
	char	*cwd;
	int		status;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	status = chdir(newpath);
	env_set(node->shell, "OLDPWD", ft_strcat("OLDPWD=", cwd));
	free(cwd);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	env_set(node->shell, "PWD", ft_strcat("PWD=", cwd));
	free(cwd);
	return (status);
}

static int	do_the_jump(t_ast *node, char *jump)
{
	char	*path;
	int		status;

	if (jump[0] == '~')
		path = ft_strdup(env_get(node->shell, "HOME"));
	else
		path = ft_strdup(jump);
	status = change_the_directory(path, node);
	return (free(path), status);
}

static int	handle_tilde(t_ast *node, char *path)
{
	char	*start;
	char	*end;
	char	*jump;
	int		status;

	start = path;
	while (*start)
	{
		end = start;
		while (*end && *end != '/')
			end++;
		jump = ft_strcut(start, end);
		status = do_the_jump(node, jump);
		free(jump);
		jump = NULL;
		if (status != 0)
			return (1);
		start = end;
		if (*start == '/')
			start++;
	}
	return (0);
}

static int	too_many_args_error(t_ast *node)
{
	ft_putstr_fd(node->shell->name, STDERR_FILENO);
	ft_putstr_fd(": cd: too many arguments\n", STDERR_FILENO);
	return (1);
}

int	builtin_cd(t_ast *node)
{
	int		status;
	char	*path;

	if (!node->tokens[1])
	{
		path = ft_strdup(env_get(node->shell, "HOME"));
		status = change_the_directory(path, node);
		return (free(path), status);
	}
	if (string_array_len(node->tokens) > 2)
		return (too_many_args_error(node));
	path = ft_strdup(node->tokens[1]);
	if (handle_tilde(node, path) != 0)
		return (free(path), 1);
	else
		return (free(path), 0);
}
