/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:25:41 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/15 20:02:06 by jvoisard         ###   ########.fr       */
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
	PARSE_ERROR
}	t_parser_state;

typedef struct s_parser
{
	t_parser_state		state;
	char				*line;
	t_string			token;
	t_list				*tokens;
}	t_parser;

void	input_parse_default(t_parser *parser);

#endif