/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:02:13 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/01 08:56:28 by dyodlm           ###   ########.fr       */
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

static int	get_operator_type(char *op)
{
	int			i;
	static int	operators[] = {
	{"&&", INPUT_AND},
	{"||", INPUT_OR},
	{"|", INPUT_PIPE},
	{"<<", INPUT_REDIR},
	{NULL, 0}
	};

	i = 0;
	while (operators[i].op)
	{
		if (!ft_strcmp(operators[i].op, op))
			return (operators[i].op);
		i++;
	}
	return (0);
}

int	get_stack_state(t_input *input, int len)
{
	return (check_string(input->stack));
}

static int	check_whitespaces(char *echo, char *to_find)
{
	size_t	i;

	i = 0;
	while (echo[i] == to_find[0] || ft_isspace(echo[i]))
		i++;
	if (i == ft_strlen(echo))
		return (get_operator_type(to_find));
	return (0);
}

int	find_last_operator(char *line, char *to_find)
{
	size_t	len;
	int		type;
	char	*echo;
	char	*next;

	len = ft_strlen(line);
	echo = ft_strnstr(line, to_find, len);
	if (!echo)
		return (0);
	next = ft_strnstr(echo, to_find, ft_strlen(echo));
	if (!next)
		type = check_whitespaces(echo, to_find);
	else
	{
		while (next)
		{
			free(echo);
			echo = next;
			next = ft_strnstr(echo, to_find, ft_strlen(echo));			
		}
		type = check_whitespaces(echo, to_find);
	}
	return (free(echo), type);
}


/* u.x itere sur la string 	&&	u.jiest actif si quote
	&& u.j pour dquote 	&& 	u.k est actif si parentheses ouvertes	*/
int	get_last_token_type(t_input *input)
{
	int		token_type;

	token_type = find_last_operator(input->stack, "&&");
	if (token_type)
		return (token_type);
	token_type = find_last_operator(input->stack, "||");
	if (token_type)
		return (token_type);
	token_type = find_last_operator(input->stack, "|");
	if (token_type)
		return (token_type);
	token_type = find_last_operator(input->stack, "<<");
	if (token_type)
		return (token_type);
	return (0);
}
