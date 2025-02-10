/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:27:29 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/10 16:04:47 by jvoisard         ###   ########.fr       */
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

void	debug_node(t_sh *shell, t_ast *node, int call)
{
	static int	deep = 0;

	(void)call;
	if (!node)
		return (throw_error("ast empty", __FILE__, __LINE__));
	debug(shell, "TYPE IS : \n");
	if (node->type == AST_COMMAND)
	{
		debug(shell, "[Command]\n");
		while (node->args && node->args[i] != NULL)
			debug(shell, node->args[i++]);
		debug(shell, "\n");
	}
	if (node->type == AST_PIPELINE)
		debug(shell, "[Pipe node]\n");
	if (node->type == AST_LOGICAL)
		debug(shell, "[Logical]\n");
	if (node->type == AST_REDIRECT)
		debug(shell, "[Redirect] \n");
	if (node->left)
		debug_node(shell, node->left, 0);
	if (node->right)
		debug_node(shell, node->right, 0);
	debug(shell, "\n\n");
}
