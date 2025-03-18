/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_wildcard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:17:56 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/18 15:22:45 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	match(char *filename, t_wild *wild)
{
	char	**sections;
	char	*f;

	f = filename;
	if (wild->is_wild_start && *f == '.')
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
	char			cwd[1024];
	char			**files;

	files = NULL;
	getcwd(cwd, 1024);
	dirp = opendir(cwd);
	if (!dirp)
		return (shell_exit(node->shell));
	dp = (struct dirent *)1;
	while (dp)
	{
		dp = readdir(dirp);
		if (dp && match(dp->d_name, wild))
			string_array_push(&files, ft_strcat_arr((char *[]){
					"'",
					dp->d_name,
					"'",
					NULL}));
	}
	closedir(dirp);
	string_array_sort_alpha(files);
	wild->files = string_array_join(files, " ");
	string_array_free(&files);
}

static void	wild_free(t_wild *wild)
{
	string_array_free(&wild->sections);
	if (wild->files)
	{
		free(wild->files);
		wild->files = NULL;
	}
	if (wild->pattern)
	{
		free(wild->pattern);
		wild->pattern = NULL;
	}
}

static bool	wild_init_pattern(t_ast *node, t_wild *wild, char *line)
{
	char	*cursor;

	wild_free(wild);
	wild->start = ast_tokens_find(line, "*");
	if (!wild->start)
		return (false);
	wild->end = wild->start;
	while (*wild->end && !ft_isspace(*wild->end))
		wild->end++;
	while (wild->start > line && !ft_isspace(*wild->start))
		wild->start--;
	wild->start++;
	wild->pattern = ast_take_word(node, wild->start);
	if (!wild->pattern)
		return (true);
	wild->sections = ft_split(wild->pattern, '*');
	if (!wild->sections)
		return (wild_free(wild), shell_exit(node->shell), false);
	wild->is_wild_start = *wild->pattern == '*';
	cursor = wild->pattern;
	while (*cursor)
		cursor++;
	wild->is_wild_end = *(cursor - 1) == '*';
	return (true);
}

void	ast_parse_wildcard(t_ast *node)
{
	t_wild		wild;
	t_string	line;
	int			i;

	ft_bzero(&wild, sizeof(wild));
	line.value = NULL;
	string_push_str(&line, node->line);
	i = 0;
	while (line.value[i] && wild_init_pattern(node, &wild, line.value + i))
	{
		i = wild.start - line.value;
		wild_get_files(node, &wild);
		if (!wild.files)
		{
			i += ft_strlen(wild.pattern);
			continue ;
		}
		string_replace(&line, wild.start, wild.end, wild.files);
		i += ft_strlen(wild.files);
	}
	wild_free(&wild);
	free(node->line);
	node->line = line.value;
}
