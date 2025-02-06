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

static void	pars_end_check(t_sh *shell)
{
	if (shell->ast.log == 0)
		shell->ast.type = AST_COMMAND;
	if (!ft_strncmp(shell->lexer.tokens[0], "exitshell",
			ft_strlen(shell->lexer.tokens[0])))
		shell_exit(shell);
}

void	parse_free(t_sh *shell)
{
	(void)shell;
	debug(shell, "Freeing AST ???\n");
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
	type = pars_get_type(*shell->lexer.tokens);
	while (args)
	{
		if (type == AST_COMMAND)
			args++;
		else if (type == AST_REDIRECT || type == AST_LOGICAL)
		{
			shell->ast = pars_handle_processes(args, shell, type);
			shell->ast.log++;
			args++;
		}
		else if (type == AST_END)
			break ;
		type = pars_get_type(*args);
	}
	pars_end_check(shell);
}
