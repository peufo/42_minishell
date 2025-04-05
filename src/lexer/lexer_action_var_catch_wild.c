/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_action_var_catch_wild.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:35:20 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/05 15:11:07 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_action_var_catch_wild(t_lexer *lexer, int var_len)
{
	char	*token;

	token = lexer->token.value;
	if (!token)
		return ;
	while (*token)
		token++;
	token -= var_len;
	if (token < lexer->token.value)
		return ;
	while (*token)
	{
		if (*token == '*')
			string_array_push(&lexer->wilds, token);
		token++;
	}
}
