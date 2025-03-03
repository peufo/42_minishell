/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:02:13 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/03 07:14:41 by dyodlm           ###   ########.fr       */
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

static int	check_whitespaces(char *echo, char *to_find, t_input *input)
{
	size_t	i;
	char	*find_redir;

	i = 0;
	find_redir = NULL;
	printf("Checking whitespaces\n");
	if (!input->redir_code)
		find_redir = ft_strrchrstr(echo, "<<");
	while (echo[i] == to_find[0] || ft_isspace(echo[i]))
		i++;
	if (i == ft_strlen(echo) && (!input || !input->is_redir))
		return (get_operator_type(to_find));
	else if (find_redir)
	{
		while (ft_isspace(*find_redir) || *find_redir == to_find[0])
			find_redir++;
		if (!ft_isalnum(*find_redir))
			return (0);
		return (INPUT_REDIR);
	}
	return (0);
}

static int	find_last_operator(char *line, char *to_find, t_input *input)
{
	int		type;
	char	*echo;

	echo = ft_strrchrstr(line, to_find);
	if (!echo)
		return (0);
	type = check_whitespaces(echo, to_find, input);
	return (type);
}

int	get_last_token_type(char *line, t_input *input)
{
	int		token_type;
	
	if (input->state == INPUT_DQUOTE || input->state == INPUT_QUOTE)
		return (0);
	token_type = find_last_operator(line, "&&", input);
	if (token_type)
		return (token_type);
	token_type = find_last_operator(line, "||", input);
	if (token_type)
		return (token_type);
	token_type = find_last_operator(line, "|", input);
	if (token_type)
		return (token_type);
	token_type = find_last_operator(line, "<<", input);
	if (token_type)
		return (token_type);
	return (0);
}
