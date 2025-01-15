/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:34:52 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/15 20:02:22 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parser_state	get_next_state(t_parser *parser)
{
	static t_parser_state	next_stats[][255] = {
	[PARSE_DEFAULT]['"'] = PARSE_DQUOTE,
	[PARSE_DEFAULT]['\''] = PARSE_QUOTE,
	[PARSE_DEFAULT]['$'] = PARSE_VAR,
	[PARSE_QUOTE]['\''] = PARSE_DEFAULT,
	[PARSE_DQUOTE]['$'] = PARSE_VAR_DQUOTE,
	[PARSE_DQUOTE]['"'] = PARSE_DEFAULT,
	[PARSE_VAR_DQUOTE][' '] = PARSE_DQUOTE,
	[PARSE_VAR_DQUOTE]['\t'] = PARSE_DQUOTE,
	[PARSE_VAR_DQUOTE]['"'] = PARSE_DEFAULT,
	[PARSE_VAR]['"'] = PARSE_DQUOTE,
	[PARSE_VAR][' '] = PARSE_DEFAULT,
	[PARSE_VAR]['\t'] = PARSE_DEFAULT
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
	input_parse_exit(&parser);
	shell->tokens = parser.tokens;
}
