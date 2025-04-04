/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:40:04 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/03 17:24:54 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_input_line(t_sh *shell)
{
	if (shell->input.line)
	{
		free(shell->input.line);
		shell->input.line = NULL;
	}
	return (true);
}

static void	check_sig_out(t_input *input, t_sh *shell)
{
	(void)shell;
	if (!g_is_sigint)
		return ;
	shell->exit_status = 130;
	if (input->line)
	{
		free(input->line);
		input->line = NULL;
	}
	input_free(input);
}

static bool	lex_eof_read_input(t_sh *shell, t_input *input)
{
	if (g_is_sigint)
	{
		shell->exit_status = 130;
		g_is_sigint = false;
	}
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
		if (g_is_sigint)
			break ;
	}
	if (g_is_sigint)
		return (check_sig_out(input, shell), false);
	return (check_sig_out(input, shell), true);
}

void	get_safe_readline_inputs(t_sh *shell, t_input *input)
{
	shell->line2 = NULL;
	if (check_input_line(shell) && shell->line)
		transfer_shell_line(shell);
	else
	{
		while ((!input->line || !*input->line)
			|| (!input->redir_line || !*input->redir_line))
		{
			if (g_is_sigint)
				break ;
			if (input->is_redir)
				assure_heredoc_line(shell);
			else
				assure_eof_line(shell);
			if (!input->line && !input->redir_line && !input->is_redir)
				shell_exit(shell);
			if (input->line && is_empty_line(input->line))
			{
				free(input->line);
				input->line = NULL;
			}
			else
				break ;
		}
	}
}

/*	if (did_eye_of_sawron(shell, 1)) return (false); */
bool	lex_eof(t_sh *shell)
{
	return (printf("Parse error\n"), false);
	if (shell->line)
		shell->input.state = check_string(shell->line);
	else
		shell->input.state = check_string(shell->input.line);
	shell->input.last = get_last_token_type(shell->line, &shell->input);
	if (shell->input.state > 0 || shell->input.last > 0)
	{
		if (!lex_eof_read_input(shell, &shell->input))
		{
			shell->input.line = ft_strdup(shell->line2);
			while (!lex_eof_read_input(shell, &shell->input))
				continue ;
		}
		if (!is_empty_line(shell->input.stack))
			add_history(shell->input.stack);
	}
	if (shell->input.stack && 1)
		shell->line = ft_strdup(shell->input.stack);
	if (shell->line2)
	{
		free(shell->line);
		shell->line = shell->line2;
	}
	return (true);
}
