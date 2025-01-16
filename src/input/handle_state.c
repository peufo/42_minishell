/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:49:27 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/16 19:14:48 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_state_default(t_parser *parser)
{
	string_push(&parser->token, *parser->line);
	parser->line++;
}

static void	handle_state_dquote(t_parser *parser)
{
	string_push(&parser->token, *parser->line);
	parser->line++;
}

static void	handle_state_quote(t_parser *parser)
{
	string_push(&parser->token, *parser->line);
	parser->line++;
}

void	handle_state(t_parser *parser)
{
	t_state_handler			handler;
	static t_state_handler	handlers[] = {
	[PARSE_DEFAULT] = handle_state_default,
	[PARSE_QUOTE] = handle_state_quote,
	[PARSE_DQUOTE] = handle_state_dquote,
	[PARSE_VAR] = handle_state_var,
	[PARSE_VAR_DQUOTE] = handle_state_var_dquote,
	};

	handler = handlers[parser->state];
	if (handler)
		handler(parser);
}
