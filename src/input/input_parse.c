/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:34:52 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/16 15:55:18 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parser_state	get_next_state(t_parser *parser)
{
	static t_parser_state	next_stats[][256] = {
	[PARSE_DEFAULT]['"'] = PARSE_DQUOTE,
	[PARSE_DEFAULT]['\''] = PARSE_QUOTE,
	[PARSE_DEFAULT]['$'] = PARSE_VAR,
	[PARSE_DEFAULT][' '] = PARSE_END_TOKEN,
	[PARSE_DEFAULT]['\t'] = PARSE_END_TOKEN,
	[PARSE_DEFAULT]['\n'] = PARSE_END_TOKEN,
	[PARSE_QUOTE]['\''] = PARSE_DEFAULT,
	[PARSE_DQUOTE]['"'] = PARSE_DEFAULT,
	[PARSE_DQUOTE]['$'] = PARSE_VAR_DQUOTE,
	[PARSE_VAR_DQUOTE]['"'] = PARSE_DEFAULT,
	[PARSE_VAR_DQUOTE][' '] = PARSE_DQUOTE,
	[PARSE_VAR_DQUOTE]['\t'] = PARSE_DQUOTE,
	[PARSE_VAR]['"'] = PARSE_DQUOTE,
	[PARSE_VAR]['\''] = PARSE_QUOTE,
	[PARSE_VAR][' '] = PARSE_END_TOKEN,
	[PARSE_VAR]['\t'] = PARSE_END_TOKEN,
	[PARSE_VAR]['\n'] = PARSE_END_TOKEN
	};

	return (next_stats[parser->state][(int)*(parser->line)]);
}

static void	input_line_to_tokens(t_parser *parser)
{
	t_parser_state	next_state;

	while (*(parser->line) && parser->state != PARSE_ERROR)
	{
		next_state = get_next_state(parser);
		if (next_state)
		{
			parser->state = next_state;
			parser->line++;
			continue ;
		}
		handle_state(parser);
	}
	if (parser->state != PARSE_ERROR)
	{
		parser->state = PARSE_END_TOKEN;
		handle_state(parser);
	}
}

static void	input_parse_exit(t_parser *parser)
{
	if (parser->token.value)
	{
		free(parser->token.value);
		parser->token.value = NULL;
	}
	ft_lstclear(&parser->tokens, free);
}

void	input_parse(t_sh *shell)
{
	t_parser	parser;

	ft_memset(&parser, 0, sizeof(parser));
	parser.line = shell->line;
	parser.state = PARSE_DEFAULT;
	input_line_to_tokens(&parser);
	if (parser.state == PARSE_ERROR)
		input_parse_exit(&parser);
	shell->tokens = parser.tokens;
}
