/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_wilcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:17:56 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/05 15:10:42 by jvoisard         ###   ########.fr       */
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
	if (!sections || !*sections)
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

static void	wild_get_files(t_lexer *lexer, t_wild *wild)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			cwd[4096];
	char			**files;

	files = NULL;
	getcwd(cwd, 4096);
	dirp = opendir(cwd);
	if (!dirp)
		return (shell_exit(lexer->node->shell));
	dp = (struct dirent *)1;
	while (dp)
	{
		dp = readdir(dirp);
		if (dp && match(dp->d_name, wild))
			string_array_push(&files, ft_strdup(dp->d_name));
	}
	closedir(dirp);
	string_array_sort_alpha(files);
	wild->files = files;
}

static void	wild_free(t_wild *wild)
{
	string_array_free(&wild->sections);
	string_array_free(&wild->files);
}

static bool	wild_init(t_lexer *lexer, t_wild *wild)
{
	char	*cursor;
	char	**wilds;

	cursor = lexer->token.value;
	wilds = lexer->wilds;
	wild->is_wild_start = cursor == *wilds;
	while (*wilds)
	{
		if (*wilds != cursor)
		{
			string_array_push(&wild->sections, ft_strcut(cursor, *wilds));
			if (!wild->sections)
				return (wild_free(wild), shell_exit(lexer->node->shell), false);
		}
		cursor = *wilds + 1;
		wilds++;
	}
	wilds--;
	cursor = lexer->token.value;
	while (*cursor)
		cursor++;
	wild->is_wild_end = (cursor - 1) == *wilds;
	if (!wild->is_wild_end)
		string_array_push(&wild->sections, ft_strcut((*wilds + 1), NULL));
	return (true);
}

void	lexer_expand_wildcard(t_lexer *lexer)
{
	t_wild	wild;
	char	**files;

	ft_bzero(&wild, sizeof(wild));
	if (!lexer->wilds)
		return ;
	if (wild_init(lexer, &wild))
	{
		wild_get_files(lexer, &wild);
		files = wild.files;
		if (files)
		{
			string_free(&lexer->token);
			while (*files)
				string_array_push(&lexer->tokens, ft_strdup(*(files++)));
		}
	}
	wild_free(&wild);
	free(lexer->wilds);
	lexer->wilds = NULL;
}
