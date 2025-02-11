/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:27:29 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/11 11:10:40 by dyodlm           ###   ########.fr       */
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
	t_utils	u;

	ft_bzero(&u, sizeof(t_utils));
	if (!node)
		return (throw_error("ast NULL", __FILE__, __LINE__));
	while (u.i++ < call)
		debug(shell, "  ");
	if (node->type == AST_COMMAND)
	{
		debug(shell, "[Command]: ");
		while (node->args && node->args[u.j])
			debug_arr(shell, (char *[]){"cmd:", node->args[u.j++], "\n", NULL});
	}
	else if (node->type == AST_LOGICAL)
		debug_arr(shell, (char *[]){"[Logical] : (&&)\n", NULL});
	else if (node->type == AST_PIPELINE)
		debug(shell, "[Pipeline] (|)\n");
	else if (node->type == AST_REDIRECT)
		debug(shell, "[Redirect] (>>) \n");
	if (node->left)
		debug_node(shell, node->left, call + 1);
	if (node->right)
		debug_node(shell, node->right, call + 1);
	debug(shell, "\n\n");
}
