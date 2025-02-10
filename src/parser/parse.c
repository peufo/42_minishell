/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:24:16 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/10 08:05:55 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static void	pars_pull_operators(t_sh *shell, t_nstack *ops, t_nstack *tmp)
{
	(void)ops;
	(void)shell;
	(void)tmp;
}

static void	free_2dtab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (throw_error("Nothing to free :", __FILE__, __LINE__));
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
}

static char	**pars_actualise_tokens(t_sh *shell, char **nativ, int start)
{
	int		i;
	char	**ntoks;

	i = 0;
	debug(shell, "redefining argument \n");
	ntoks = malloc((parse_toks_len(nativ) - (start - 2)) * sizeof(char *));
	if (!ntoks)
		return (throw_error("malloc in :", __FILE__, __LINE__), NULL);
	while (nativ[start + i] != NULL)
	{
		ntoks[i] = ft_strdup(nativ[start + i]);
		i++;
	}
	ntoks[i] = NULL;
	debug(shell, "arguments redefined\n");
	return (ntoks);
}

static t_ast	*pars_handle_processes(char **toks, int t_len, t_sh *shell)
{
	t_nstack	*tmp;
	t_nstack	*ops;
	char		**ntoks;
	int			type;
	int			i;

	i = 0;
	ops = NULL;
	tmp = NULL;
	while (i < t_len)
	{
		printf("looping1\n");
		ntoks = pars_actualise_tokens(shell, toks, i++);
		type = pars_get_type(*ntoks);
		printf("cursor reasigned \n");
		if (type == AST_LOGICAL || type == AST_PIPELINE)
			parse_handle_logical(shell, tmp, ops, type);
		else if (type == AST_REDIRECT)
			parse_handle_redirection(shell, tmp, ntoks);
		else
			parse_push_node(shell, &tmp, parse_node_command(*ntoks));
		free_2dtab(ntoks);
		ntoks = NULL;
		printf("end of loop\n");
	}
	printf("out of the loop\n");
	while (ops)
		pars_pull_operators(shell, ops, tmp);
	printf("Did we did it ???\n");
	debug_node(shell, tmp->ast, 0);
	return (tmp->ast);
}*/

void	parse(t_sh *shell)
{
	int		b;

	if (!shell->lexer.tokens)
	{
		shell->ast->args = NULL;
		return ;
	}
	shell->ast = malloc(sizeof(shell->ast));
	if (!shell->ast)
		return (throw_error("WTF \n", __FILE__, __LINE__));
	if (shell->lexer.tokens != NULL)
		shell->ast->args = shell->lexer.tokens;
	b = check_for_simple_pars(shell, shell->lexer.tokens);
	if (!b)
		return (throw_error("Line too complex\n", __FILE__, __LINE__));
	else if (b == 1)
		return (debug(shell, "Only words\n"));
	shell->ast->args = parse_collector(shell->lexer.tokens);
	debug_new_tokens(shell, shell->ast->args);
	debug(shell, "\n INTO HANDLE SCRIPT | \n");
	shell->ast = parse_handle_script(shell->ast->args,
		parse_toks_len(shell->ast->args), shell);
	debug(shell, "\n OUT OF SCRIPT HANDLING\n");
	debug_ast(shell);
	return (shell_exit(shell));
}
