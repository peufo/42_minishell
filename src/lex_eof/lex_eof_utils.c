/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:02:13 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/27 10:29:13 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_get_type(char *tok)
{
	int				i;
	static t_ttype	ttype[] = {
	{"&&", 3},
	{"||", 3},
	{"|", 2},
	{"(", 5},
	{"<", 4},
	{">", 4},
	{">>", 4},
	{"<<", 4},
	{NULL, 0}
	};

	i = 0;
	if (tok == NULL)
		return (AST_NULL);
	while (ttype[i].tok)
	{
		if (!ft_strcmp(ttype[i].tok, tok))
			return (ttype[i].op);
		i++;
	}
	return (1);
}

int	get_stack_state(t_input *input)
{
	int	state;

	state = 0;
	(void)input;
	return (state);
}

int	get_last_token_type(t_input *input)
{
	int	token_type;

	token_type = 0;
	(void)input;
	return (token_type);
}
