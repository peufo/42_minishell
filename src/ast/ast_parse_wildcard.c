/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_wildcard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:17:56 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/14 00:25:54 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	match(char *filename, char *pattern)
{
	(void)filename;
	(void)pattern;
	return (true);
}

static char	**get_files(t_ast *node, char *pattern)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			**files;

	files = NULL;
	dirp = opendir(env_get(node->shell, "PWD"));
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
		if (match(dp->d_name, pattern))
			string_array_push(&files, ft_strdup(dp->d_name));
	}
	closedir(dirp);
	return (files);
}

static char	*get_pattern(t_ast *node, char *line)
{
	char	*wild;

	wild = ast_tokens_find(line, "*");
	DEBUG("WILD: %s\n", wild);
	if (!wild)
		return (NULL);
	while (wild > line && !ft_isspace(*wild))
		wild--;
	DEBUG("WILD: %s\n", wild);
	return (ast_take_word(node, wild));
}

void	ast_parse_wildcard(t_ast *node)
{
	char	**files;
	char	*pattern;
	int		i;

	pattern = get_pattern(node, node->line);
	DEBUG("PATTERN: %s\n", pattern);
	if (!pattern)
		return ;
	files = get_files(node, pattern);
	free(pattern);
	pattern = NULL;
	if (!files)
		return ;
	i = 0;
	while (files[i])
		DEBUG("FILE: %s\n", files[i++]);
	string_array_free(&files);
}
