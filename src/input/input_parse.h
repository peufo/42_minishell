/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:25:41 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/16 00:40:55 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_PARSE_H
# define INPUT_PARSE_H
# include "libft.h"
# include "utils/string.h"

typedef enum e_parser_state
{
	PARSE_NO_STATE,
	PARSE_DEFAULT,
	PARSE_QUOTE,
	PARSE_DQUOTE,
	PARSE_VAR,
	PARSE_VAR_DQUOTE,
	PARSE_ERROR,
	PARSE_END_TOKEN
}	t_parser_state;

typedef struct s_parser
{
	t_parser_state		state;
	char				*line;
	t_string			token;
	t_list				*tokens;
}	t_parser;

typedef void	(*t_char_handler)(t_parser *);

void	handle_state(t_parser *parser);

#endif