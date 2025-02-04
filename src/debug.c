/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:27:29 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/04 17:50:00 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_tokens(t_sh *shell)
{
	t_list	*current;
	char	*token;

	current = shell->lexer.tokens;
	debug(shell, "\nTokens received:\n");
	while (current)
	{
		token = current->content;
		debug_arr(shell, (char *[]){
			"[",
			token,
			"]\n",
			NULL
		});
		current = current->next;
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
	debug(shell, "\nAST: ");
	debug(shell, "TODO");
	debug(shell, "\n");
}
