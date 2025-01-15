/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:34:52 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/15 18:43:45 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "input_parse.h"

static t_parser_state	get_next_state(t_parser *parser)
{
	static t_parser_state	next_stats[5][255] = {
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
	char			current;

	while (*(parser->line))
	{
		next_state = get_next_state(parser);
		current = *(parser->line++);
		if (next_state)
		{
			parser->state = next_state;
			continue ;
		}
		ft_putchar_fd(current, STDOUT_FILENO);
	}
}

void	input_parse(t_sh *shell)
{
	t_parser	parser;

	ft_memset(&parser, 0, sizeof(parser));
	parser.line = shell->line;
	parser.state = PARSE_DEFAULT;
	input_line_to_tokens(&parser);
	shell->tokens = parser.tokens;
	ft_putstr_fd("TODO parse: ", shell->pipe.out);
	ft_putstr_fd(shell->line, shell->pipe.out);
}
