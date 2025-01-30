/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:22:03 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/30 15:31:56 by jvoisard         ###   ########.fr       */
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

int	check_string(char *input)
{
	int	popen;
	int	pclos;
	int	index;

	popen = 0;
	pclos = 0;
	index = 0;
	while (input[index])
	{
		if (input[index] == '"')
		{
			if (!look_inside_dquo(input, &index))
				return (throw_error("Unclosed dquote", __FILE__, __LINE__), 0);
		}
		else if (input[index] == '\'')
		{
			if (!look_inside_squo(input, &index))
				return (throw_error("Unclosed squote", __FILE__, __LINE__), 0);
		}
		else
			helper(input, &popen, &pclos, &index);
	}
	if (pclos != popen)
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
