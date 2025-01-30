/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:24:16 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/30 15:22:20 by jvoisard         ###   ########.fr       */
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
		{
			printf("- [%s]\nArgument type : ", token->value.value);
			printf("%s\n", token->type);
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
		return (throw_error("No tokens received", WHERE));
	print_tokens(shell->lexer.tokens);
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
