/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 04:36:07 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/01 11:04:40 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (shell->line)
	{
		input->line = ft_strdup(shell->line);
		free(shell->line);
		shell->line = NULL;
	}
	else
	{
		while (!input->line || !*input->line)
		{
			input->line = readline("EOF >");
			if (!input->line)
				shell_exit(shell);
			if (input->line && is_empty_line(input->line))
				input->line = NULL;
			else
				break ;
		}
	}
}

static void	lex_eof_checkout(t_input *input)
{
	char	*res;

	res = input->stack;
	input->state = 0;
	(void)res;
	add_history(input->stack);
}

static void	lex_eof_read_input(t_sh *shell, t_input *input)
{
	while (input->state > 0 || input->last > 0)
	{
		get_safe_readline_inputs(shell, input);
		stack_to_buffer(&input->stack, input->line);
		if (shell->line)
		{
			free(shell->line);
			shell->line = NULL;
		}
		input->state = check_string(input->stack);
//		printf("State is : %d\n", input->state);
		input->last = get_last_token_type(input->stack);
//		printf("Last operator is : %d\n", input->last);
//		printf("Stack is : %s\n", input->stack);
		if (input->state <= 0 && input->last <= 0)
			return (lex_eof_checkout(input));
//		printf("NOT OUT\n");
		free(input->line);
		input->line = NULL;
	}
}

void	lex_eof(t_sh *shell)
{
	t_input		*input;

	input = ft_calloc(1, sizeof(t_input));
	input->state = LEXER_DEFAULT;
	while (input->state > 0 || input->last > 0)
	{
		lex_eof_read_input(shell, input);
	//	printf("Stack is %s\n", input->stack);
	//	debug_arr(shell, (char *[]){"State in handler is ",
	//		ft_itoa(input->state), "\n", NULL});
	}
	if (input->stack)
		shell->line = ft_strdup(input->stack);
	else
		shell_exit(shell);
}
