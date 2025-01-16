/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:25:41 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/16 19:14:20 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_PARSE_H
# define INPUT_PARSE_H
# include "libft.h"
# include "utils/string.h"

typedef enum e_parser_state
{
	PARSE_NO_STATE,
	PARSE_INIT,
	PARSE_DEFAULT,
	PARSE_QUOTE,
	PARSE_DQUOTE,
	PARSE_VAR,
	PARSE_VAR_DQUOTE,
}	t_parser_state;

typedef struct s_parser
{
	t_parser_state		state;
	char				*line;
	t_string			token;
	t_string			varname;
	t_list				*tokens;
}	t_parser;

typedef void	(*t_state_handler)(t_parser *);
typedef void	(*t_transition_handler)(t_parser *);

void	handle_state(t_parser *parser);
void	handle_state_var(t_parser *parser);
void	handle_state_var_dquote(t_parser *parser);
void	handle_transition(t_parser *parser, t_parser_state next_state);

#endif