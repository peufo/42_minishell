#include "minishell.h"

static int	look_inside_squo(char *input, int *start);

static int	look_inside_dquo(char *input, int *start)
{
	while (input[*start] && input[*start] != '"')
	{
		if (input[*start] == '\'')
			look_inside_squo(input, start);
		(*start)++;
	}
	if (input[*start] != '"')
		return (0);
	return (1);
}

static int	look_inside_squo(char *input, int *start)
{
	while (input[*start] && input[*start] != '\'')
	{
		if (input[*start] == '"')
			look_inside_dquo(input, start);
		(*start)++;
	}
	if (input[*start] != '\'')
		return (0);
	return (1);
}

static void	helper(char *input, int *popen, int *pclos, int *start)
{
	if (input[*start] == '(')
		popen++;
	if (input[*start] == ')')
		pclos++;
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
		if (!input[index])
			break ;
		helper(input, &popen, &pclos, &index);
	}
	if (pclos != popen)
		return (message(UNMATCHED_PAR, CHECK_STRING), 0);
	return (1);
}
