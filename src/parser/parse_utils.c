/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:11:07 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/11 07:50:26 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_free(t_sh *shell)
{
	int	i;

	i = 0;
	pars_free_ast(shell->ast);
	debug(shell, "\\\\\\\\\\\\\\\\\\\\\\ Out Of debug mode ////////////\n");
	return (debug(shell, "ast freed ! freed !!!\n"));
	debug(shell, "\n");
	if (!shell->ast->args)
		return ;
	while (shell->ast->args[i] != NULL)
		free(shell->ast->args[i++]);
	free(shell->ast->args);
	free(shell->ast);
	debug(shell, "ast freed !\n");
}

static char	*assemble(char **toks, int n, int start)
{
	int		len;
	int		i;
	char	*a;

	i = 0;
	if (n == 2)
		return (ft_strjoin(toks[start], toks[start + 1]));
	else
	{
		len = 0;
		while (toks[start + i])
			len += ft_strlen(toks[start + i++]) + 1;
		a = malloc(len * sizeof(char) + 1);
		if (!a)
			return (throw_error("malloc in : ", __FILE__, __LINE__), NULL);
		i = 0;
		ft_memset(a, 0, len + 1);
		while (i < n && pars_get_type(toks[start + i]) == AST_COMMAND)
		{
			ft_strlcat(a, toks[start + i++], len);
			ft_strlcat(a, " ", len);
		}
	}
	return (a);
}

static void	repeat_process(char ***toks, char ***ntoks, int **types, t_utils *u)
{
	while ((*toks)[u->i] != NULL)
	{
		u->k = 0;
		(*types)[u->k++] = pars_get_type((*toks)[u->i++]);
		while ((*toks)[u->i] != NULL && (*types)[u->k - 1] == AST_COMMAND)
			(*types)[u->k++] = pars_get_type((*toks)[u->i++]);
		if (u->k > 2)
		{
			(*ntoks)[u->j++] = assemble(*toks, u->k, u->i - u->k);
			if ((*toks)[u->i - 1] != NULL && (*toks)[u->i] != NULL)
				(*ntoks)[u->j++] = ft_strdup((*toks)[-1 + u->i]);
		}
		else if ((*toks)[u->i - 1] != NULL && 2)
		{
			if ((*toks)[u->i] != NULL)
				(*ntoks)[u->j++] = ft_strdup((*toks)[u->i - 2]);
			else if ((*types)[u->k - 1] == AST_COMMAND)
				(*ntoks)[u->j++] = assemble(*toks, 3, u->i - u->k);
			else
				(*ntoks)[u->j++] = ft_strdup((*toks)[u->i - 1]);
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
	ntoks = malloc(parse_toks_len(toks) * sizeof(char *));
	if (!ntoks)
		return (throw_error("malloc in :", __FILE__, __LINE__), NULL);
	types = malloc(parse_toks_len(toks) * sizeof(int));
	if (!types)
		return (free(ntoks), throw_error("malloc:", __FILE__, __LINE__), NULL);
	repeat_process(&toks, &ntoks, &types, &u);
	free(types);
	return (ntoks);
}
