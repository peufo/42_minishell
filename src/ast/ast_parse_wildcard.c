/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_wildcard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:17:56 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/14 22:39:35 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	match(char *filename, t_wild *wild)
{
	char	**sections;
	char	*f;

	f = filename;
	if (!ft_strcmp(f, ".") || !ft_strcmp(f, ".."))
		return (false);
	sections = wild->sections;
	if (!*sections)
		return (true);
	if (!wild->is_wild_start && !ft_startwith(f, *(sections++)))
		return (false);
	while (*sections)
	{
		while (*f && !ft_startwith(f, *sections))
			f++;
		if (!*f)
			return (false);
		f += ft_strlen(*sections);
		sections++;
	}
	if (!wild->is_wild_end && !ft_endwith(filename, *(sections - 1)))
		return (false);
	return (true);
}

static void	wild_get_files(t_ast *node, t_wild *wild)
{
	DIR				*dirp;
	struct dirent	*dp;

	dirp = opendir(env_get(node->shell, "PWD"));
	if (!dirp)
	{
		errno = false;
		return ;
	}
	while (true)
	{
		dp = readdir(dirp);
		if (!dp)
			break ;
		if (match(dp->d_name, wild))
		{
			if (wild->files.value)
				string_push_str(&wild->files, " ");
			string_push_str(&wild->files, dp->d_name);
		}
	}
	closedir(dirp);
	return ;
}

static void	wild_free(t_wild *wild)
{
	string_free(&wild->files);
	string_array_free(&wild->sections);
	if (wild->pattern)
	{
		free(wild->pattern);
		wild->pattern = NULL;
	}
}

static void	wild_init_pattern(t_ast *node, t_wild *wild, char *line)
{
	char	*cursor;

	wild_free(wild);
	wild->start = ast_tokens_find(line, "*");
	if (!wild->start)
		return ;
	wild->end = wild->start;
	while (*wild->end && !ft_isspace(*wild->end))
		wild->end++;
	while (wild->start > line && !ft_isspace(*wild->start))
		wild->start--;
	wild->start++;
	wild->pattern = ast_take_word(node, wild->start);
	if (!wild->pattern)
		return ;
	wild->sections = ft_split(wild->pattern, '*');
	if (!wild->sections)
		return (wild_free(wild), shell_exit(node->shell));
	wild->is_wild_start = *wild->pattern == '*';
	cursor = wild->pattern;
	while (*cursor)
		cursor++;
	wild->is_wild_end = *(cursor - 1) == '*';
	return ;
}

void	ast_parse_wildcard(t_ast *node)
{
	t_wild		wild;
	t_string	line;
	int			i;

	wild.files.value = NULL;
	line.value = NULL;
	string_push_str(&line, node->line);
	wild.pattern = NULL;
	wild.sections = NULL;
	i = 0;
	while (line.value[i])
	{
		wild_init_pattern(node, &wild, line.value + i);
		if (!wild.pattern || !wild.start)
			break ;
		i = wild.start - line.value;
		wild_get_files(node, &wild);
		if (!wild.files.value)
		{
			i += ft_strlen(wild.pattern);
			continue;
		}
		string_replace(&line, wild.start, wild.end, wild.files.value);
		i += ft_strlen(wild.files.value);
	}
	wild_free(&wild);
	free(node->line);
	node->line = line.value;
}
