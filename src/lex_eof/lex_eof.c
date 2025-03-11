/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 04:36:07 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/11 10:30:47 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
		if (!ft_isspace(line[i++]))
			return (false);
	return (true);
}

static bool	check_input_line(t_sh *shell)
{
	if (shell->input.line)
	{
		free(shell->input.line);
		shell->input.line = NULL;
	}
	return (true);
}

void	get_safe_readline_inputs(t_sh *shell, t_input *input)
{
	if (check_input_line(shell) && shell->line)
		transfer_shell_line(shell);
	else
	{
		while ((!input->line || !*input->line)
			|| (!input->redir_line || !*input->redir_line))
		{
			if (get_the_fucking_line(shell))
				break ;
		}
	}
}
/*
static void	handle_chaos(t_sh *shell)
{
	printf("\n\nDEBUG START\n\n");
	printf("Shell Line : %s\n", shell->line);
	printf("Input Line : %s\n", shell->input->line);
	printf("State : %d\nLast : %d\n", shell->input->state, shell->input->last);
	printf("Stack at : %s\n", shell->input->stack);
	printf("\n\nDEBUG END\n\n");
}*/

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
		input->last = get_last_token_type(input->stack, input);
		stack_to_history(input->stack, shell);
	}
}

void	lex_eof(t_sh *shell)
{
	if (shell->line)
		shell->input.state = check_string(shell->line);
	else
		shell->input.state = check_string(shell->input.line);
	shell->input.last = get_last_token_type(shell->line, &shell->input);
	if (shell->input.state > 0 || shell->input.last > 0)
		lex_eof_read_input(shell, &shell->input);
	if (shell->input.stack)
		shell->line = ft_strdup(shell->input.stack);
	else
		shell_exit(shell);
}
