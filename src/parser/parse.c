/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:24:16 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/30 16:05:34 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_free(t_sh *shell)
{
	(void)shell;
}

void	process_token(t_token *token)
{
	if (!token || !token->value.value)
		return ;
}

static void	print_tokens(t_sh *shell)
{
	t_list	*current;
	t_token	*token;

	current = shell->lexer.tokens;
	debug(shell, "Tokens received:");
	while (current)
	{
		token = (t_token *)current->content;
		if (token && token->value.value)
		{
			debug_arr(shell, (char *[]){
				"- [",
				token->value.value,
				"]\n",
				token->type,
				"\n",
				NULL
			});
		}
		else
			printf("- [NULL or invalid token]\n");
		current = current->next;
	}
}

void	parse(t_sh *shell)
{
	t_list	*current;
	t_token	*token;

	if (!shell || !shell->lexer.tokens)
		return (throw_error("No tokens received", __FILE__, __LINE__));
	print_tokens(shell);
	current = shell->lexer.tokens;
	while (current)
	{
		token = (t_token *)current->content;
		if (!token || !token->value.value)
			current = current->next;
		process_token(token);
		current = current->next;
	}
}
