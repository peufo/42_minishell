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

void	parse_free(t_sh *shell)
{
	(void)shell;
}

void	parse(t_sh *shell)
{
	t_token 	*token;
	t_list 		*current_token;
	t_list		*tokens = shell->lexer.tokens;

	if (!tokens)
		return ;
	shell->parser.cmd->args = tokens;
	shell->parser.cmd->pipe.in = STDIN_FILENO;
	shell->parser.cmd->pipe.out = STDOUT_FILENO;
	current_token = tokens;
	while (current_token)
	{
		token = (t_token *)current_token->content;
		if (token)
			printf("Token : %s\n", token->value.value);
		current_token = current_token->next;
	}
	if ((char *)shell->parser.cmd->args->content)
	{
		(void)tokens;
	}
}