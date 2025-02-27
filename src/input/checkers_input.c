/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:00:56 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/23 10:03:55 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	look_inside_squo(char *input, int *start);

static int	look_inside_dquo(char *input, int *start)
{
	(*start)++;
	while (input[*start])
	{
		if (input[*start] == '"')
			return ((*start)++, 1);
		(*start)++;
	}
	return (0);
}

static int	look_inside_squo(char *input, int *start)
{
	(*start)++;
	while (input[*start])
	{
		if (input[*start] == '\'')
			return ((*start)++, 1);
		(*start)++;
	}
	return (0);
}

static void	helper(char *input, int *popen, int *pclos, int *start)
{
	if (input[*start] == '(')
		(*popen)++;
	if (input[*start] == ')')
		(*pclos)++;
	(*start)++;
}

/*	u.k est l'index		||	u.i par open 	|| 	u.j par close	*/
int	check_string(char *input)
{
	t_utils	u;

	if (!input)
		return (0);
	ft_bzero(&u, sizeof(t_utils));
	while (input[u.k])
	{
		if (input[u.k] == '"')
		{
			if (!look_inside_dquo(input, &u.k))
				return (0);
		}
		else if (input[u.k] == '\'')
		{
			if (!look_inside_squo(input, &u.k))
				return (0);
		}
		else
			helper(input, &u.i, &u.j, &u.k);
	}
	if (u.j != u.i)
		return (throw_error("Unclosed parentheses", __FILE__, __LINE__), 0);
	return (1);
}

int	check_double(t_lexer *lexer, char c)
{
	lexer->cursor++;
	if (*lexer->cursor == c)
	{
		lexer->cursor--;
		return (1);
	}
	lexer->cursor--;
	return (0);
}
