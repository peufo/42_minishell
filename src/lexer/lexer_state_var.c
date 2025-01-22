/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_state_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:26:29 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/22 14:09:40 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_state_var(t_lexer *lexer)
{
	string_push(&lexer->token, *lexer->line);
	lexer->line++;
}

void	lexer_state_var_dquote(t_lexer *lexer)
{
	string_push(&lexer->token, *lexer->line);
	lexer->line++;
}
