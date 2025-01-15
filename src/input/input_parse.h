/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:25:41 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/15 18:10:48 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_PARSE_H
# define INPUT_PARSE_H
# include "libft.h"

typedef enum e_parser_state
{
	PARSE_DEFAULT,
	PARSE_QUOTE,
	PARSE_DQUOTE,
	PARSE_VAR,
	PARSE_VAR_DQUOTE
}	t_parser_state;

typedef struct s_parser
{
	t_parser_state		state;
	t_parser_state		next_states[5][256];
	char				*line;
	char				*token;
	t_list				*tokens;
}	t_parser;

#endif