/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:02:13 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/28 15:29:49 by dyodlm           ###   ########.fr       */
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

static int	get_operator_type(char *buffer, int len)
{
	while (0 == 1)
		(void)buffer;
	return (0);
}
int	get_stack_state(t_input *input, int len)
{
	int	state;

	state = 0;
	(void)input;
	return (state);
}

static int	check_validity(char *buffer, int len)
{
	int	type;

	type = 0;
	(void)buffer;
	return (type);
}

static bool	is_meta_char(char c)
{
	if (c == '&' || c == '|' || c == '>' || c == '<')
		return (true);
	return (false);
}

/* u.x itere sur la string 	&&	u.jiest actif si quote
	&& u.j pour dquote 	&& 	u.k est actif si parentheses ouvertes	*/
int	get_last_token_type(t_input *input)
{
	int	i;
	int	token_type;

	i = 0;
	if (input->stack && input->state <= 1)
		return (0);
	while (input->stack[i])
		i++;
	if (i > 1)
	{
		if (is_meta_char(input->stack))
			token_type = check_validity(input->stack, i);
	}
	else if (i == 1)
		token_type = get_operator_type(input->stack, i);
	return (token_type);
}
