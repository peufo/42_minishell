/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:07:05 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/03 10:55:29 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	checkout_from_logic(t_input *input)
{
	input->is_redir = false;
	if (!g_is_sigint)
		return (true);
	return (false);
	if (input->redir_input)
		string_array_free(&input->redir_input);
	if (input->redir_code)
		string_array_free(&input->redir_code);
	return (false);
}

bool	check_heredoc_code(char *s1, char *s2)
{
	if (!s1 || !s2 || ft_strlen(s1) != ft_strlen(s2))
		return (false);
	if (!ft_strncmp(s1, s2, ft_strlen(s1)))
		return (true);
	return (false);
}

bool	apply_redir_logic(t_input *input, t_sh *shell)
{
	int	i;

	i = 0;
	input->is_redir = true;
	while (i < input->nb_redir)// &&input->line || input->redir_line) &&
	{
		stack_to_buffer(&input->redir_input[i], input->redir_line);
		if (input->redir_line)
		{
			if (check_heredoc_code(input->redir_line, input->redir_code[i]))
				i++;
		}
		else if (input->line)
		{
			if (check_heredoc_code(input->line, input->redir_code[i]))
				i++;
		}
		free(input->redir_line);
		input->redir_line = NULL;
		if (i == input->nb_redir || g_is_sigint)
			break ;
		get_safe_readline_inputs(shell, input);
		if (!input->redir_line && !input->line)
			i++;
	}
	return (checkout_from_logic(input));
}

static void	shell_is_shit(t_sh *shell, char **str, char *copy)
{
	if (str && *str)
		free(*str);
	*str = NULL;
	if (shell->line)
		free(shell->line);
	shell->line = copy;
}

bool	treat_redirections(t_input *input, t_sh *shell)
{
	char	*cursor;
	char	*head;
	char	*copy;

	input_free(input);
	copy = ft_strdup(shell->line);
	transfer_shell_line(shell);
	if (!shell->input.stack && shell->input.line)
		cursor = ft_strdup(shell->input.line);
	else
		cursor = ft_strdup(shell->input.stack);
	head = cursor;
	safe_init_redir_array(shell, input);
	get_all_codes(input, cursor);
	if (!input && !input->redir_line)
		input->redir_line = input->line;
	shell->line = head;
	if (!apply_redir(shell, copy))
		return (false);
	shell_is_shit(shell, &input->line, copy);
	return (checkout_from_redir(shell), true);
}
