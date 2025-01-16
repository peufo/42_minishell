/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_state_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:26:29 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/16 16:31:34 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_state_var(t_parser *parser)
{
	string_push(&parser->token, *parser->line);
	parser->line++;
}

void	handle_state_var_dquote(t_parser *parser)
{
	string_push(&parser->token, *parser->line);
	parser->line++;
}
