/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:49:27 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/16 10:52:59 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_blank(t_parser *parser)
{
	while (*parser->line == ' ' || *parser->line == '\t')
		parser->line++;
}

static void	handle_state_default(t_parser *parser)
{
	skip_blank(parser);
	string_push(&parser->token, *parser->line);
	parser->line++;
}

static void	handle_state_end_token(t_parser *parser)
{
	printf("ADD TOKEN : %s\n", parser->token.value);
	ft_lstadd_back(&parser->tokens, ft_lstnew(parser->token.value));
	parser->token.value = NULL;
	parser->state = PARSE_DEFAULT;
}

void	handle_state(t_parser *parser)
{
	t_char_handler			handler;
	static t_char_handler	handlers[] = {
	[PARSE_DEFAULT] = handle_state_default,
	[PARSE_QUOTE] = handle_state_default,
	[PARSE_DQUOTE] = handle_state_default,
	[PARSE_VAR] = handle_state_default,
	[PARSE_VAR_DQUOTE] = handle_state_default,
	[PARSE_END_TOKEN] = handle_state_end_token
	};

	handler = handlers[parser->state];
	if (handler)
		handler(parser);
}
