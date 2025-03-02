/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:02:13 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/02 06:50:47 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_operator_type(char *op)
{
	int					i;
	static t_operator	operators[] = {
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
			return ((int)operators[i].type);
		i++;
	}
	return (0);
}

int	get_stack_state(t_input *input)
{
	return (check_string(input->stack));
}

static int	check_whitespaces(char *echo, char *to_find)
{
	size_t	i;
	char	*is_redir;

	i = 0;
	is_redir = ft_strrchrstr(echo, "<<");
	while (echo[i] == to_find[0] || ft_isspace(echo[i]))
		i++;
	if (i == ft_strlen(echo) && !is_redir)
		return (get_operator_type(to_find));
	else if (is_redir)
	{
		while (ft_isspace(*is_redir) || *is_redir == to_find[0])
			is_redir++;
		if (!ft_isalnum(*is_redir))
			return (0);
		return (INPUT_REDIR);
	}
	return (0);
}

static int	find_last_operator(char *line, char *to_find)
{
	int		type;
	char	*echo;

	echo = ft_strrchrstr(line, to_find);
	if (!echo)
		return (0);
	type = check_whitespaces(echo, to_find);
	return (type);
}

int	get_last_token_type(char *input, char *is_redir)
{
	int		token_type;

	if (is_redir)
		return (INPUT_REDIR);
	token_type = find_last_operator(input, "&&");
	if (token_type)
		return (token_type);
	token_type = find_last_operator(input, "||");
	if (token_type)
		return (token_type);
	token_type = find_last_operator(input, "|");
	if (token_type)
		return (token_type);
	token_type = find_last_operator(input, "<<");
	if (token_type)
		return (token_type);
	return (0);
}
