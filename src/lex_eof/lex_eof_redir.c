/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:07:05 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/18 10:25:24 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	transfer_shell_line(t_sh *shell)
{
	shell->input.line = ft_strdup(shell->line);
	free(shell->line);
	shell->line = NULL;
}

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

static bool	apply_redir_logic(t_input *input, t_sh *shell)
{
	int	i;

	i = 0;
	input->is_redir = true;
	while ((input->line || input->redir_line) && i < input->nb_redir)
	{
		stack_to_buffer(&input->redir_input[i], input->redir_line);
		if (input->redir_line)
		{
			if (!ft_strncmp(input->redir_line,
					input->redir_code[i],
					ft_strlen(input->redir_code[i])))
				i++;
		}
		else if (input->line)
		{
			if (!ft_strcmp(input->line, input->redir_code[i]))
				i++;
		}
		if (i == input->nb_redir)
			break ;
		get_safe_readline_inputs(shell, input);
	}
	input->is_redir = false;
	return (true);
}

int	count_redir_in_line(t_sh *shell, char *line, bool dquote, bool quote)
{
	char	*head;
	char	*cursor;
	int		count;

	count = 0;
	head = ft_strdup(line);
	cursor = head;
	if (!cursor)
		return (0);
	while (*cursor)
	{
		check_quotes(*cursor, &dquote, &quote);
		if (!dquote && !quote && check_redir(cursor))
		{
			count++;
			while (*cursor == '<' || ft_isspace(*cursor))
				cursor++;
			while (ft_isalnum(*cursor))
				cursor++;
		}
		else
			cursor++;
	}
	(void)shell;
	return (free(head), count);
}

void	treat_redirections(t_input *input, t_sh *shell)
{
	char	*cursor;
	char	*head;

	head = ft_strdup(shell->line);
	if (shell->line)
		transfer_shell_line(shell);
	safe_init_redir_array(shell, input);
	if (!input->stack)
		cursor = ft_strdup(input->line);
	else
		cursor = ft_strdup(input->stack);
	get_all_codes(input, cursor);
	if (!input->redir_line)
		input->redir_line = input->line;
	if (!apply_redir_logic(input, shell))
		return (shell_exit(shell));
	checkout_from_redir(shell);
	shell->line = head;
	free(cursor);
}
