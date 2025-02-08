/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:24:16 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/08 09:08:11 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pars_pull_operators(t_sh *shell, t_nstack *ops, t_nstack *tmp)
{
	(void)ops;
	(void)shell;
	(void)tmp;
}

static t_ast	*pars_handle_processes(char ***toks, int t_len, t_sh *shell)
{
	t_nstack	*tmp;
	t_nstack	*ops;
	char		**cmd;
	int			type;
	int			i;

	i = 0;
	ops = NULL;
	tmp = NULL;
	while (i < t_len)
	{
		printf("looping1\n");
		cmd = *toks;
		type = pars_get_type(cmd[0]);
		printf("cursor reasign \n");
		if (type == AST_LOGICAL || type == AST_PIPELINE)
			parse_handle_logical(shell, tmp, ops, type);
		else if (type == AST_REDIRECT)
			parse_handle_redirection(shell, tmp, cmd);
		else
			parse_push_node(shell, &tmp, parse_node_command(*cmd));
		toks++;
		i++;
		printf("end of loop\n");
	}
	printf("out of the loop\n");
	while (ops)
		pars_pull_operators(shell, ops, tmp);
	printf("Did we did it ???\n");
	debug_node(shell, tmp->ast, 0);
	return (tmp->ast);
}

void	parse(t_sh *shell)
{
	int		b;
	int		t_len;

	if (!shell->lexer.tokens)
	{
		shell->ast->args = NULL;
		return ;
	}
	t_len = 0;
	shell->ast = malloc(sizeof(shell->ast));
	if (!shell->ast)
		return (throw_error("WTF \n", __FILE__, __LINE__));
	b = check_for_simple_pars(shell, shell->lexer.tokens);
	if (!b)
		return (throw_error("Line too complex \n", __FILE__, __LINE__));
	else if (b == 1)
	{
		shell->ast->args = shell->lexer.tokens;
		return (debug(shell, "Only words\n"));
	}
	shell->ast->args = parse_collector(shell->lexer.tokens);
	t_len = parse_toks_len(shell->ast->args);
	debug_new_tokens(shell, shell->ast->args);
	shell->ast = pars_handle_processes(&shell->ast->args, t_len, shell);
	pars_end_check(shell);
}
