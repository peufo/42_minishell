/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:27:29 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/07 07:27:48 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_tokens(t_sh *shell)
{
	char	**tokens;

	tokens = shell->lexer.tokens;
	if (!tokens)
	{
		debug(shell, "NO TOKENS\n");
		return ;
	}
	debug(shell, "\nTOKENS:\n");
	while (*tokens)
	{
		debug_arr(shell, (char *[]){
			"[",
			*tokens,
			"]\n",
			NULL
		});
		tokens++;
	}
}

void	debug_input(t_sh *shell)
{
	debug_arr(shell, (char *[]){
		"============\n",
		"INPUT: ",
		shell->line,
		NULL
	});
}

void	debug_ast(t_sh *shell)
{
	debug(shell, "\n");
}

static void debug_right_part(t_sh *shell, t_ast *node)
{
    if (node->left)
    {
        debug(shell, "[RIGHT SUBTREE]\n");
        debug_node(shell, node->right, 1);
    }
}

static void debug_left_part(t_sh *shell, t_ast *node)
{
    if (node->left)
    {
        debug(shell, "[LEFT SUBTREE]\n");
        debug_node(shell, node->left, 1);
    }
}

void    debug_node(t_sh *shell, t_ast *node, int call)
{
    int i;

    i = 0;
    debug(shell, "TYPE IS :\n");
    if (node->type == AST_COMMAND)
    {
        debug(shell, "[Command]\n");
        while (node->args && node->args[i] != NULL)
           debug(shell, node->args[i++]);
        debug(shell, "\n");
    }
    else if (node->type == AST_PIPELINE)
        debug(shell, "[Pipe node]\n");
    else if (node->type == AST_LOGICAL)
    {
        debug(shell, "[Logical]\n");
        if (node->op == AST_OP_OR)
            debug(shell, "[AND]\n");
        else
            debug(shell, "[OR]\n");
    }
    if (call == 0)
    {
        debug_left_part(shell, node);
        debug_right_part(shell, node);
    }
    debug(shell, "\n\n");
}
