/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:24:16 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/05 14:59:38 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_free(t_sh *shell)
{
	(void)shell;
	debug(shell, "Freeing AST ???\n");
}

t_ast   parse_logical(char **tokens)
{
	t_aop	op;
    t_ast	left;
    t_ast   right;
    t_ast   origin;

    left = parse_commands(tokens);
    origin = left;
    while (*tokens && check_gates(tokens))
	{
		op = AST_OP_NULL;
		if (!ft_strncmp(*tokens, "&&", ft_strlen(*tokens)))
			op = AST_OP_AND;
		else if (!ft_strncmp(*tokens, "||", ft_strlen(*tokens)))
			op = AST_OP_OR;
		tokens++;
		right = parse_commands(tokens);
		origin = parse_node_ast(AST_LOGICAL, op, &left, &right);
	}
	return (origin);
}

t_ast   parse_commands(char **tokens)
{
    t_ast	node;
	
	node.type = AST_COMMAND;
	node.args = parse_collector(tokens);
	return (node);
}

t_ast	parse_pipeline(char **tokens)
{
	t_ast	left;
	t_ast	right;
	t_ast	origin;

	left = parse_logical(tokens);
	origin = left;
	while (*tokens && ft_strncmp(*tokens, "|", ft_strlen(*tokens)))
	{
		tokens++;
		right = parse_logical(tokens);
		origin = parse_node_ast(AST_PIPELINE, AST_OP_NULL, &left, &right);
		left = origin;
	}
	return (origin);
}

t_ast	pars_handle_processes(char **tokens, t_sh *shell, int type)
{
	t_ast	node;

	if (type == AST_REDIRECT)
	{
		debug(shell, "\nREDIRECTION WAS PARSED\n");
		node = parse_redirection(tokens);
	}
	else if (type == AST_PIPELINE)
	{
		debug(shell, "\nPIPELINE WAS PARSED\n");
		node = parse_pipeline(tokens);
	}
	else if (type == AST_LOGICAL)
	{
		debug(shell, "\nLOGICAL WAS PARSED\n");
		node = parse_logical(tokens);
	}
	else
	{
		debug(shell, "\nCOMMAND WAS PARSED\n");
		node = parse_commands(tokens);
	}

	debug(shell, "DEFINE TYPE :");
	debug(shell, ft_itoa(type));
	debug(shell, "\n\n");
	debug_node(shell, &node);
	debug(shell, "well...\n");
	return (node);
}

void	parse(t_sh *shell)
{
	int		type;
	char	**args;

	if (!shell->lexer.tokens)
	{
		shell->ast.args = NULL;
		return ;
	}
	args = shell->lexer.tokens;
	shell->ast.type = AST_SCRIPT;
	shell->ast.args = shell->lexer.tokens;
	type = pars_get_type(*shell->lexer.tokens);
	while (args)
	{
		if (type == AST_COMMAND)
			args++;
		else if (type == AST_REDIRECT || type == AST_LOGICAL)
		{
			shell->ast = pars_handle_processes(args, shell, type);
			args++;
		}
		else if (type == AST_END)
			break ;
		type = pars_get_type(*args);
	}
}
