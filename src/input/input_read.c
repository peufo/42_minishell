/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:36:57 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/28 10:38:09 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

void	input_free(t_input *input)
{
	if (!input)
		return ;
	if (input->redir_code)
		string_array_free(&input->redir_code);
	if (input->redir_input)
		string_array_free(&input->redir_input);
	if (input->line)
	{
		free(input->line);
		input->line = NULL;
	}
	if (input->stack)
	{
		free(input->stack);
		input->stack = NULL;
	}
	if (input->redir_line)
	{
		free(input->redir_line);
		input->redir_line = NULL;
	}
	ft_memset(input, 0, sizeof(t_input));
}

static bool	lex_check_start(char *line, t_input *input)
{
	if (!line)
		return (BASIC_MOD);
	if (check_string(line) || get_last_token_type(line, input))
		return (BONUS_MOD);
	return (BASIC_MOD);
}

static bool	iss_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
		if (!ft_isspace(line[i++]))
			return (0);
	return (1);
}

int	input_read(t_sh	*shell)
{
	shell_update_prompt(shell);
	if (shell->line)
	{
		free(shell->line);
		shell->line = NULL;
	}
	if (shell->is_interactive)
	{
		shell->line = readline(shell->prompt.value);
		if (!shell->line || iss_empty_line(shell->line))
			return (shell_exec(shell), -1);
		errno = false;
		if (!lex_check_start(shell->line, &shell->input))
		{
			if (!iss_empty_line(shell->line))
				add_history(shell->line);
		}
	}
	else
		shell->line = get_next_line(shell->pipe.in);
	if (errno)
		shell_exit(shell);
	if (shell->line && iss_empty_line(shell->line))
		return (shell_exec(shell), -1);
	return (lex_check_start(shell->line, &shell->input));
}
