/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_action_var_catch_wild.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:35:20 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/25 17:39:38 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_action_var_catch_wild(t_ast *node, int var_len)
{
	char	*token;

	token = node->lexer.token.value;
	if (!token)
		return ;
	while (*token)
		token++;
	token -= var_len;
	if (token < node->lexer.token.value)
		return ;
	while (*token)
	{
		if (*token == '*')
			string_array_push(&node->lexer.wilds, token);
		token++;
	}
}
