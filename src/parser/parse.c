/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:24:16 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/22 15:02:26 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "macros.h"

void	parse_free(t_sh *shell)
{
	(void)shell;
}

void	process_token(t_token *token)
{
	if (!token || !token->value.value)
		return ;
	printf("Processing token: %s\n", token->value.value);
}

void	print_tokens(t_list *tokens)
{
	t_list	*current;
	t_token	*token;

	current = tokens;
	printf("Tokens received:\n");
	while (current)
	{
		token = (t_token *)current->content;
		if (token && token->value.value)
			printf("- [%s]\n", token->value.value);
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
	{
		message(TOKEN_PROBLEM, PARSE);
		return ;
	}
	print_tokens(shell->lexer.tokens);
	current = shell->lexer.tokens;
	while (current)
	{
		token = (t_token *)current->content;
		if (!token || !token->value.value)
		{
			message(BULLSHIT, 234);
			current = current->next;
		}
		process_token(token);
		current = current->next;
	}
}
