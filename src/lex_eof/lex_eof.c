/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 04:36:07 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/02 07:04:24 by dyodlm           ###   ########.fr       */
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

static char	*catch_the_redir_code(char *line)
{
	int		i;
	int		len;
	char	*res;
	char	*tmp;

	i = 0;
	len = 0;
	tmp = ft_strrchrstr(ft_strdup(line), "<<");
	while (ft_isspace(tmp[i]) || tmp[i] == '<')
		i++;
	while (ft_isalnum(tmp[i + len]))
		len++;
	res = ft_calloc(len + 1, sizeof(char));
	len = 0;
	while (ft_isalnum(tmp[i]))
		res[len++] = tmp[i++];
	res[len] = '\0';
	return (res);
}

static bool	lex_eof_checkout(t_input *input)
{
	if (input->last != INPUT_REDIR && input->state > 0 && input->last > 0)
		return (false);
	if (input->redir_code)
	{
		if (!ft_strcmp(input->line, input->redir_code))
		{
			input->last = 0;
			input->state = 0;
			return (true);
		}
	}
	else if (input->last == INPUT_REDIR)
	{
		input->state = INPUT_REDIR;
		input->redir_code = catch_the_redir_code(input->line);
		return (false);
	}
	return (true);
}

static void	lex_eof_read_input(t_sh *shell, t_input *input)
{
	bool	out;

	out = false;
	while ((input->state > 0 || input->last > 0) && out == false)
	{
		get_safe_readline_inputs(shell, input);
		stack_to_buffer(&input->stack, input->line);
		if (shell->line)
		{
			free(shell->line);
			shell->line = NULL;
		}
		input->state = check_string(input->stack);
		input->last = get_last_token_type(input->stack, input->redir_code);
		out = lex_eof_checkout(input);
		add_history(input->stack);
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
		lex_eof_read_input(shell, input);
	if (input->stack)
		shell->line = ft_strdup(input->stack);
	else
		shell_exit(shell);
}
