/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:07:05 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/25 12:09:17 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_all_codes(t_input *input, char *cursor)
{
	int		i;
	char	*tmp;
	char	*buf;

	i = 0;
	if (!cursor)
		return ;
	buf = ft_strchrstr(cursor, "<<");
	while (buf && i < input->nb_redir)
	{
		input->redir_code[i++] = catch_the_redir_code(buf);
		while (*buf == '<' || ft_isspace(*buf))
			buf++;
		while (ft_isalnum(*buf))
			buf++;
		tmp = ft_strchrstr(buf, "<<");
		buf = tmp;
	}
}

static bool	checkout_from_logic(t_input *input)
{
	input->is_redir = false;
	if (!g_signal.is_sigint)
		return (true);
	return (false);
	if (input->redir_input)
		string_array_free(&input->redir_input);
	if (input->redir_code)
		string_array_free(&input->redir_code);
	return (false);
}

static bool	check_heredoc_code(char *s1, char *s2)
{
	if (!s1 || !s2 || ft_strlen(s1) - 1 != ft_strlen(s2))
		return (false);
	if (!ft_strncmp(s1, s2, ft_strlen(s1) - 1))
		return (true);
	return (false);
}

bool	apply_redir_logic(t_input *input, t_sh *shell)
{
	int	i;

	i = 0;
	input->is_redir = true;
	while ((input->line || input->redir_line) && i < input->nb_redir)
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
		if (i == input->nb_redir || g_signal.is_sigint)
			break ;
		get_safe_readline_inputs(shell, input);
	}
	return (checkout_from_logic(input));
}

bool	treat_redirections(t_input *input, t_sh *shell)
{
	char	*cursor;
	char	*head;
	char	*copy;

	shell->line2 = NULL;
	copy = ft_strdup(shell->line);
	transfer_shell_line(shell);
	if (!shell->input.stack)
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
		return (true);
	shell->line = copy;
	checkout_from_redir(shell);
	return (true);
}
