/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:34:52 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/19 22:21:54 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parser_state	get_next_state(t_parser *parser)
{
	static t_parser_state	next_stats[][256] = {
	[PARSE_DEFAULT]['"'] = PARSE_DQUOTE,
	[PARSE_DEFAULT]['\''] = PARSE_QUOTE,
	[PARSE_DEFAULT]['$'] = PARSE_VAR,
	[PARSE_DEFAULT][' '] = PARSE_DEFAULT,
	[PARSE_DEFAULT]['\t'] = PARSE_DEFAULT,
	[PARSE_DEFAULT]['\n'] = PARSE_DEFAULT,
	[PARSE_QUOTE]['\''] = PARSE_DEFAULT,
	[PARSE_DQUOTE]['"'] = PARSE_DEFAULT,
	[PARSE_DQUOTE]['$'] = PARSE_VAR_DQUOTE,
	[PARSE_VAR_DQUOTE]['"'] = PARSE_DEFAULT,
	[PARSE_VAR_DQUOTE][' '] = PARSE_DQUOTE,
	[PARSE_VAR_DQUOTE]['\t'] = PARSE_DQUOTE,
	[PARSE_VAR]['"'] = PARSE_DQUOTE,
	[PARSE_VAR]['\''] = PARSE_QUOTE,
	[PARSE_VAR][' '] = PARSE_DEFAULT,
	[PARSE_VAR]['\t'] = PARSE_DEFAULT,
	[PARSE_VAR]['\n'] = PARSE_DEFAULT
	};

	return (next_stats[parser->state][(int)*(parser->line)]);
}

static void	input_line_to_tokens(t_parser *parser)
{
	t_parser_state	next_state;

	while (*(parser->line))
	{
		next_state = get_next_state(parser);
		if (next_state)
			handle_transition(parser, next_state);
		else
			handle_state(parser);
	}
	handle_transition(parser, PARSE_DEFAULT);
}

// TODO: handle error malloc
static void	tokens_to_commands(t_parser *parser)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return ;
	cmd->executable = parser->tokens->content;
	cmd->args = parser->tokens;
	cmd->pipe.in = STDIN_FILENO;
	cmd->pipe.out = STDOUT_FILENO;
	ft_lstadd_back(&parser->commands, ft_lstnew(cmd));
}

void	input_parse(t_sh *shell)
{
	t_parser	parser;

	ft_memset(&parser, 0, sizeof(parser));
	parser.line = shell->line;
	parser.state = PARSE_INIT;
	handle_transition(&parser, PARSE_DEFAULT);
	input_line_to_tokens(&parser);
	string_free(&parser.token);
	string_free(&parser.varname);
	tokens_to_commands(&parser);
	shell->tokens = parser.tokens;
	shell->commands = parser.commands;
}
