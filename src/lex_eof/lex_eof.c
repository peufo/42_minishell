/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 04:36:07 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/07 11:29:23 by dyodlm           ###   ########.fr       */
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

static bool	check_input_line(t_sh *shell)
{
	if (shell->input->line)
	{
		free(shell->input->line);
		shell->input->line = NULL;
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
			if (input->is_redir)
				input->redir_line = readline("redir-mode > ");
			else
				input->line = readline("> ");
			if (!input->line && !input->redir_line)
				shell_exit(shell);
			if (input->line && is_empty_line(input->line))
				input->line = NULL;
			else
				break ;
			if (input->redir_line && is_empty_line(input->redir_line))
				input->redir_line = NULL;
			else
				break ;
			if (!input->line)
				input->line = input->redir_line;
		}
	}
}

static void	lex_eof_read_input(t_sh *shell, t_input *input)
{
	int	count;

	while (input->state > 0 || input->last > 0)
	{
		get_safe_readline_inputs(shell, input);
		if (shell->line)
			count = count_redir_in_line(shell, shell->line, false, false);
		else if (input->line)
			count = count_redir_in_line(shell, input->line, false, false);
		printf("Count of redirs : %d\n", count);
		if (count > 0)	
			treat_redirections(input, shell);
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
	debug(shell, "In eof\n");
	shell->input->state = check_string(shell->input->line);
	shell->input->last = get_last_token_type(shell->line, shell->input);
	while (shell->input->state > 0 || shell->input->last > 0)
		lex_eof_read_input(shell, shell->input);
	if (shell->input->stack)
		shell->line = ft_strdup(shell->input->stack);
	else
		shell_exit(shell);
}
