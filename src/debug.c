/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:27:29 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/06 10:14:08 by dyodlm           ###   ########.fr       */
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
