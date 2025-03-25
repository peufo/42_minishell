/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:40:04 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/25 07:55:21 by dyodlm           ###   ########.fr       */
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
			if (g_signal.is_sigint)
				break ;
			if (input->is_redir)
			{
				ft_putstr_fd(">>", 1);
				input->redir_line = get_line(STDIN_FILENO);
			}
			else
				input->line = readline("> ");
			if (!input->line && !input->redir_line)
				shell_exit(shell);
			if (input->line && is_empty_line(input->line))
				input->line = NULL;
			else
				break ;
		}
	}
}

static void	check_sig_out(t_input *input, t_sh *shell)
{
	(void)input;
	if (!g_signal.is_sigint)
		return ;
	if (input->line)
	{
		free(input->line);
		input->line = NULL;
	}
	input_free(input);
	shell_exec(shell);
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
		input->last = get_last_token_type(input->stack, input);
		stack_to_history(input->stack, shell);
		if (g_signal.is_sigint)
			break ;
	}
	check_sig_out(input, shell);
}

void	lex_eof(t_sh *shell)
{
	if (shell->line)
		shell->input.state = check_string(shell->line);
	else
		shell->input.state = check_string(shell->input.line);
	shell->input.last = get_last_token_type(shell->line, &shell->input);
	if (shell->input.state > 0 || shell->input.last > 0)
	{
		lex_eof_read_input(shell, &shell->input);
		add_history(shell->input.stack);
	}
	if (shell->input.stack && 1)
		shell->line = ft_strdup(shell->input.stack);
	else
		shell_exit(shell);
}
