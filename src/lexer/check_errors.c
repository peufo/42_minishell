#include "minishell.h"

static int	look_inside_squo(char *input, int *start);

static int	look_inside_dquo(char *input, int *start)
{
	(*start)++;
	while (input[*start])
	{
		if (input[*start] == '"')
			return ((*start)++, 1);
		if (input[*start] == '\'')
		{
			if (!look_inside_squo(input, start))
				return (0);
		}
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
		if (input[*start] == '"')
		{
			if (!look_inside_dquo(input, start))
				return (0);
		}
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
				return (message(UNMATCHED_QUOTE, CHECK_STRING), 0);
		}
		else if (input[index] == '\'')
		{
			if (!look_inside_squo(input, &index))
				return (message(UNMATCHED_QUOTE, CHECK_STRING), 0);
		}
		else
			helper(input, &popen, &pclos, &index);
	}
	if (pclos != popen)
		return (message(UNMATCHED_PAR, CHECK_STRING), 0);
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