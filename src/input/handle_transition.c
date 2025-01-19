/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_transition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:21:54 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/19 22:15:10 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_transition_next_char(t_parser *parser)
{
	parser->line++;
}

static void	handle_transition_skip_blank(t_parser *p)
{
	while (*p->line == ' ' || *p->line == '\t' || *p->line == '\n')
		p->line++;
}

static void	handle_transition_preserv_dollar(t_parser *parser)
{
	if (!parser->varname.value)
		string_push(&parser->token, '$');
	parser->line++;
}

static void	handle_transition_end_token(t_parser *parser)
{
	ft_lstadd_back(&parser->tokens, ft_lstnew(parser->token.value));
	parser->token.value = NULL;
	handle_transition_skip_blank(parser);
}

void	handle_transition(t_parser *parser, t_parser_state next_state)
{
	t_transition_handler		handler;
	static t_transition_handler	handlers[][8] = {
	[PARSE_INIT][PARSE_DEFAULT] = handle_transition_skip_blank,
	[PARSE_VAR][PARSE_DQUOTE] = handle_transition_preserv_dollar,
	[PARSE_DEFAULT][PARSE_DEFAULT] = handle_transition_end_token
	};

	handler = handlers[parser->state][next_state];
	if (!handler)
		handler = handle_transition_next_char;
	handler(parser);
	parser->state = next_state;
}
