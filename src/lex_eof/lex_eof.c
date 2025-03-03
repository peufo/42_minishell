/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 04:36:07 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/03 09:07:34 by dyodlm           ###   ########.fr       */
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
			if (input->is_redir)
				input->line = readline("redir-mode > ");
			else
				input->line = readline("> ");
			if (!input->line)
				shell_exit(shell);
			if (input->line && is_empty_line(input->line))
				input->line = NULL;
			else
				break ;
		}
	}
}

static bool	lex_eof_checkout(t_input *input)
{
	printf("Last operator : %d\n", input->last);
	if ((!input->is_redir && !input->redir_code
			&& (input->state > 0 || input->last > 0)))
		return (false);
	if (input->redir_code)
	{
		stack_to_buffer(&input->redir_input, ft_strdup(input->line));
		if (!input->is_redir)
			return (true);
		else if (input->state <= 1)
			return (false);
	}
	return (true);
}

static void	lex_eof_read_input(t_sh *shell, t_input *input)
{
	bool	out;

	out = false;
	while (input->state > 0 || input->last > 0 || out == false)
	{
		printf("\n\nNEW LOOP\n\n");
		get_safe_readline_inputs(shell, input);
		stack_to_buffer(&input->stack, input->line);
		if (shell->line)
		{
			free(shell->line);
			shell->line = NULL;
		}
		if (!input->is_redir)
		{
			input->state = check_string(input->stack);
			input->last = get_last_token_type(input->stack, input);
		}
		input->is_redir = check_for_redir(input);
		debug_input_struct(shell);
		out = lex_eof_checkout(input);
		add_history(input->stack);
		free(input->line);
		input->line = NULL;
	}
}

void	lex_eof(t_sh *shell)
{
	shell->input->state = LEXER_DEFAULT;
	while (shell->input->state > 0 || shell->input->last > 0)
		lex_eof_read_input(shell, shell->input);
	if (shell->input->stack)
		shell->line = ft_strdup(shell->input->stack);
	else
		shell_exit(shell);
}
