/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 04:36:07 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/01 09:37:13 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_line(t_input *input)
{
	if (!check_string(input->stack))
		return (true);
	return (false);
}

static bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
		if (!ft_isspace(line[i++]))
			return (false);
	return (true);
}

static void	get_safe_readline_inputs(t_sh *shell, t_input *input)
{
	printf("state is : %d\n", input->state);
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
		stack_to_buffer(&input->stack, input->line);
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
}

void	lex_eof(t_sh *shell)
{
	t_input		*input;

	printf("hallo\n");
	input = ft_calloc(1, sizeof(t_input));
	input->state = LEXER_DEFAULT;
	while (input->state > 0 || input->last > 0)
	{
		printf("looping\n");
		lex_eof_read_input(shell, input);
		input->state = check_string(input->stack);
		printf("quote and unquotes are ok\n");
		input->last = get_last_token_type(input->stack);
		printf("operators checked\n");
		debug_arr(shell, (char *[]){"State in handler is ",
			ft_itoa(input->state), "\n", NULL});
	}
	if (input->stack)
		shell->line = ft_strdup(input->stack);
	else
		shell_exit(shell);
}
