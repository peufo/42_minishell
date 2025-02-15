/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:11:07 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/15 15:21:06 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_word(char *str, int start, int end)
{
	int		i;
	char	*rslt;

	if (!str)
		return (NULL);
	rslt = malloc((end - start) + 1);
	if (!rslt)
		return (NULL);
	i = 0;
	while (start < end)
		rslt[i++] = str[start++];
	rslt[i] = '\0';
	return (rslt);
}

char	**parse_word_content(t_sh *shell, char *element)
{
	t_utils	u;
	char	**cmd;

	if (!element)
		return (throw_error("NULL element in:", __FILE__, __LINE__), NULL);
	cmd = ft_calloc(3, sizeof(char *));
	if (!cmd)
		return (free(element),
			throw_error("malloc in:", __FILE__, __LINE__), NULL);
	ft_bzero(&u, sizeof(u));
	while (ft_isalnum(element[u.i]))
		u.i++;
	cmd[0] = extract_word(element, 0, u.i);
	if (!cmd[0])
		return (free(cmd), free(element), NULL);
	if (ft_isspace(element[u.i]))
		u.i++;
	while (element[u.i + u.j])
		u.j++;
	cmd[1] = extract_word(element, u.i, u.j + u.i);
	debug_arr(shell, (char *[]){"cmd :", cmd[0], "\n", NULL});
	if (!cmd[1])
		return (string_array_free(&cmd), free(element), NULL);
	cmd[2] = NULL;
	return (free(element), cmd);
}

static char	*assemble(char **toks, int n, int start)
{
	int		len;
	int		i;
	char	*a;

	i = 0;
	len = 0;
	while (toks[start + i])
		len += ft_strlen(toks[start + i++]) + 1;
	a = ft_calloc(len + 1, sizeof(char));
	if (!a)
		return (throw_error("malloc in : ", __FILE__, __LINE__), NULL);
	i = 0;
	while (i < n && parse_get_type(toks[start + i]) == AST_COMMAND)
	{
		ft_strlcat(a, toks[start + i++], len);
		ft_strlcat(a, " ", len);
	}
	return (a);
}

static void	repeat_process(char ***toks, char ***ntoks, int **types, t_utils *u)
{
	while ((*toks)[u->i] != NULL)
	{
		u->k = 0;
		(*types)[u->k++] = parse_get_type((*toks)[u->i++]);
		while ((*toks)[u->i] != NULL && (*types)[u->k - 1] == AST_COMMAND)
			(*types)[u->k++] = parse_get_type((*toks)[u->i++]);
		if (u->k > 2)
		{
			(*ntoks)[u->j++] = assemble(*toks, u->k, u->i - u->k);
			if (!(*ntoks)[u->j - 1])
				return ;
			if ((*toks)[u->i - 1] != NULL && (*toks)[u->i] != NULL)
			{
				(*ntoks)[u->j++] = ft_strdup((*toks)[-1 + u->i]);
				if (!(*ntoks)[u->j - 1])
					return ;
			}
		}
		else if ((*toks)[u->i - 1] != NULL)
		{
			if ((*toks)[u->i] != NULL)
			{
				(*ntoks)[u->j++] = ft_strdup((*toks)[u->i - 2]);
				if (!(*ntoks)[u->j - 1])
					return ;
			}
			else if ((*types)[u->k - 1] == AST_COMMAND)
			{
				(*ntoks)[u->j++] = assemble(*toks, 3, u->i - u->k);
				if (!(*ntoks)[u->j - 1])
					return ;
			}
			if ((*toks)[u->i - 1] && (*toks)[u->i] != NULL)
			{
				(*ntoks)[u->j++] = ft_strdup((*toks)[u->i - 1]);
				if (!(*ntoks)[u->j - 1])
					return ;
			}
		}
	}
	(*ntoks)[u->j] = NULL;
}

char	**parse_collector(char **toks)
{
	t_utils	u;
	int		*types;
	char	**ntoks;

	ft_bzero(&u, sizeof(u));
	ntoks = ft_calloc(string_array_len(toks), sizeof(char *));
	if (!ntoks)
		return (throw_error("malloc in :", __FILE__, __LINE__), NULL);
	types = ft_calloc(string_array_len(toks), sizeof(int));
	if (!types)
		return (string_array_free(&ntoks),
			throw_error("malloc:", __FILE__, __LINE__), NULL);
	repeat_process(&toks, &ntoks, &types, &u);
	free(types);
	string_array_free(&toks);
	return (ntoks);
}
