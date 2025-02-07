/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:24:16 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/07 11:56:47 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pars_end_check(t_sh *shell)
{
	if (shell->ast->log == 0)
	{
		shell->ast->type = AST_COMMAND;
		debug(shell, "there was only words\n");
	}
	if (!ft_strncmp(shell->lexer.tokens[0], "exitshell",
			ft_strlen(shell->lexer.tokens[0])))
		shell_exit(shell);
	shell->ast->args = shell->lexer.tokens;
}

static int	check_for_simple_pars(char **toks)
{
	int	i;
	int	type;

	i = 0;
	while (toks[i])
	{
		type = pars_get_type(toks[i++]);
		if (type == AST_LOGICAL || type == AST_SUBSHELL)
			return (0);
	}
	return (1);
}

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
		cmd = toks[i++];
		type = pars_get_type(cmd[0]);
		if (type == AST_LOGICAL || type == AST_PIPELINE)
			parse_handle_logical(shell, tmp, ops, type);
		else if (type == AST_REDIRECT)
			parse_handle_redirection(shell, tmp, cmd);
		else
			parse_push_node(shell, &tmp, parse_node_command(*cmd));
	}
	while (ops)
		pars_pull_operators(shell, ops, tmp);
	debug_node(shell, tmp->ast, 0);
	return (tmp->ast);
}

void	parse(t_sh *shell)
{
	int		t_len;

	if (!shell->lexer.tokens)
	{
		shell->ast->args = NULL;
		return ;
	}
	t_len = 0;
	debug(shell, "\n Does it collect ? \n");
	shell->ast->args = parse_collector(shell->lexer.tokens);
	debug(shell, "tokens assembled ! \n");
	t_len = parse_toks_len(shell->ast->args);
	debug_arr(shell, (char *[]){
		"The new len is : ",
		ft_itoa(t_len),
		NULL
	});
	if (!check_for_simple_pars(shell->ast->args))
		return (throw_error("Line too complex \n", __FILE__, __LINE__));
	shell->ast = pars_handle_processes(&shell->ast->args, t_len, shell);
	pars_end_check(shell);
}
