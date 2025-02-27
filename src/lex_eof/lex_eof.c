/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 04:36:07 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/27 10:33:15 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define OK 1
#
static bool	check_line(t_input *input)
{
	if (!check_string(input->stack))
		return (LINE_IS_COMPLETE);
	return (0);
}

static bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
		if (!ft_isspace(line[i++]))
			return (0);
	return (1);
}

static void	get_safe_readline_inputs(t_sh *shell, t_input *input)
{
	while (!input->line || !*input->line)
	{
		if (input->state >= 1)
			input->line = readline("EOF >");
		if (!input->line)
			shell_exit(shell);
		if (input->line && is_empty_line(input->line))
			input->line = NULL;
		else
			break ;
	}
	if (shell->line)
		input->line = ft_strdup(shell->line);
}

static void	lex_eof_checkout(t_input *input)
{
	char	*res;

	input->state = 0;
	res = ft_strjoin(input->stack, input->line);
	add_history(res);

}

static void	lex_eof_read_input(t_sh *shell, t_input *input)
{
	printf("reading input\n");
	while (1)
	{
		get_safe_readline_inputs(shell, input);
		printf("helli\n");
		stack_to_buffer(&input->stack, input->line);
		printf("helli\n");
		if (shell->line)
		{
			free(shell->line);
			shell->line = NULL;
		}
		if (check_line(input))
			return (lex_eof_checkout(input));
		free(input->line);
		input->line = NULL;
	}
	printf("boooof\n");
}

void	lex_eof(t_sh *shell)
{
	t_input		*input;

	printf("hello\n");
	input = ft_calloc(1, sizeof(t_input));
	printf("helli\n");
	while (1)
	{
		lex_eof_read_input(shell, input);
		printf("helli2\n");
		input->state = get_stack_state(input);
		printf("helli3\n");
		input->last = get_last_token_type(input);
		printf("helli4\n");
		debug_arr(shell, (char *[]){"State in handler is ",
			ft_itoa(input->state), "\n", NULL});
		if (input->state == 1 && input->last == 0)
			break ;
	}
	printf("helli\n");
	debug(shell, "\n\nOUT\n\n");
	printf("helli5\n");
	shell->line = ft_strdup(input->stack);
}
